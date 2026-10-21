#include <Windows.h>
#include <iostream>
#include <fstream>
#include <random>
#include <intrin.h>
#include "Auth/skStr.h"
#include "Protection/lazy.h"
#include "Protection/vmprotect.h"
#include "driver_extract.h"

static auto encDriverName = skCrypt(L"serenim");
const WCHAR* driverName = encDriverName.decrypt();


bool writeDriverToFile(const BYTE* data, size_t size, const WCHAR* filePath) {
    VMProtectBeginUltra(skCrypt("writeDriverToFile").decrypt());
    char narrowFilePath[MAX_PATH];
    WideCharToMultiByte(CP_UTF8, 0, filePath, -1, narrowFilePath, MAX_PATH, NULL, NULL);

    if ((GetFileAttributesW)(filePath) != INVALID_FILE_ATTRIBUTES) {
        return true;
    }

    std::ofstream file(narrowFilePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(data), size);
    if (!file.good()) {
        file.close();
        return false;
    }

    file.close();
    return true;
}

bool stopService(const WCHAR* serviceName) {
    VMProtectBeginUltra(skCrypt("stopService").decrypt());
    SC_HANDLE scmHandle = (OpenSCManagerW)(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scmHandle) {
        return false;
    }

    SC_HANDLE serviceHandle = (OpenServiceW)(scmHandle, serviceName, SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (!serviceHandle) {
        (CloseServiceHandle)(scmHandle);
        return false;
    }

    SERVICE_STATUS serviceStatus;
    if ((ControlService)(serviceHandle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        while (serviceStatus.dwCurrentState != SERVICE_STOPPED) {
            Sleep(1000);
            if (!(QueryServiceStatusEx)(serviceHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&serviceStatus, sizeof(SERVICE_STATUS), NULL)) {
                break;
            }
        }
    }

    (CloseServiceHandle)(serviceHandle);
    (CloseServiceHandle)(scmHandle);

    return serviceStatus.dwCurrentState == SERVICE_STOPPED;
}

bool deleteService(const WCHAR* serviceName) {
    VMProtectBeginUltra(skCrypt("deleteService").decrypt());

    SC_HANDLE scmHandle = (OpenSCManagerW)(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scmHandle) {
        return false;
    }

    SC_HANDLE serviceHandle = (OpenServiceW)(scmHandle, serviceName, DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (!serviceHandle) {
        if (GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST) {
            (CloseServiceHandle)(scmHandle);
            return true;
        }
        (CloseServiceHandle)(scmHandle);
        return false;
    }

    if (!stopService(serviceName)) {
        (CloseServiceHandle)(serviceHandle);
        (CloseServiceHandle)(scmHandle);
        return false;
    }

    BOOL deleted = (DeleteService)(serviceHandle);
    (CloseServiceHandle)(serviceHandle);
    (CloseServiceHandle)(scmHandle);

    return deleted == TRUE;
}

bool createService(const WCHAR* serviceName, const WCHAR* servicePath) {
    VMProtectBeginUltra(skCrypt("createService").decrypt());
    SC_HANDLE scmHandle = (OpenSCManagerW)(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
    if (!scmHandle) {
        return false;
    }

    SC_HANDLE serviceHandle = (CreateServiceW)(
        scmHandle,
        serviceName,
        serviceName,
        SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        servicePath,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    );

    bool created = serviceHandle != nullptr;
    if (created) {
        (CloseServiceHandle)(serviceHandle);
    }
    (CloseServiceHandle)(scmHandle);

    return created;
}


bool startService(const WCHAR* serviceName) {
    VMProtectBeginUltra(skCrypt("startService").decrypt());
    SC_HANDLE scmHandle = (OpenSCManagerW)(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scmHandle) {
        return false;
    }

    SC_HANDLE serviceHandle = (OpenServiceW)(scmHandle, serviceName, SERVICE_START);
    if (!serviceHandle) {
        (CloseServiceHandle)(scmHandle);
        return false;
    }

    BOOL started = (StartServiceW)(serviceHandle, 0, nullptr);
    (CloseServiceHandle)(serviceHandle);
    (CloseServiceHandle)(scmHandle);

    return started == TRUE;
}

bool renameDriverToBak(const WCHAR* originalPath) {
    std::wstring bakPath = std::wstring(originalPath) + L".bak";
    DeleteFileW(bakPath.c_str());
    if (!MoveFileExW(originalPath, bakPath.c_str(), MOVEFILE_REPLACE_EXISTING))
        return false;

    HANDLE hFile = CreateFileW(bakPath.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile != INVALID_HANDLE_VALUE) {
        LARGE_INTEGER fileSize;
        GetFileSizeEx(hFile, &fileSize);
        DWORD sz = (DWORD)fileSize.QuadPart;
        unsigned char* junk = (unsigned char*)VirtualAlloc(nullptr, sz, MEM_COMMIT, PAGE_READWRITE);
        if (junk) {
            std::mt19937 gen(__rdtsc() & 0xFFFFFFFF);
            for (DWORD i = 0; i < sz; i++)
                junk[i] = (unsigned char)(gen() & 0xFF);
            DWORD written;
            SetFilePointer(hFile, 0, nullptr, FILE_BEGIN);
            WriteFile(hFile, junk, sz, &written, nullptr);
            FlushFileBuffers(hFile);
            SecureZeroMemory(junk, sz);
            VirtualFree(junk, 0, MEM_RELEASE);
        }
        CloseHandle(hFile);
    }

    driver_extract::wipe_blob_from_memory();
    return true;
}

bool driver_init() {

    VMProtectBeginUltra(skCrypt("driver_init").decrypt());

    if (!deleteService(driverName)) {
        return false;
    }

    if (!driver_extract::extract()) {
        return false;
    }

    const std::wstring& drvPath = driver_extract::get_path();

    if (!createService(driverName, drvPath.c_str())) {
        return false;
    }

    if (startService(driverName)) {
        renameDriverToBak(drvPath.c_str());
        return true;
    }
    else {
        Sleep(500);
        if (!startService(driverName)) {
            return false;
        }
        else {
            renameDriverToBak(drvPath.c_str());
            return true;
        }
    }
}