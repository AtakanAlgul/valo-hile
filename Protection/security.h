#pragma once
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <memory>
#include <random>
#include <iphlpapi.h>
#include <winternl.h>
#include <iostream>
#include <fstream>
#include <algorithm> // std::remove_if
#include <cctype>    // isspace
#include <immintrin.h> // _mm_crc32_u32 için gerekli
#include "encryption.h"

inline void TriggerBsod() {}

#include <Wbemidl.h>
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "normaliz.lib")


#include "nlohmann/json.hpp"
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;
using namespace std;
using json = nlohmann::json;


#pragma once


#include <cstring>
#include <thread>    // For HANDLE, DWORD, CloseHandle, etc.
#include <tlhelp32.h>     // For the toolhelp snapshot functions
#include <filesystem>    // For std::ofstream      // For std::string (if skCrypt returns char*)
#include "call_spoof.h"
#include <winternl.h>
#include "Protection/lazy.h"
#pragma comment(lib, "ntdll.lib")

// ==================== ANTI-REVERSE ENGINEERING ====================

// --- Thread Hiding ---
typedef NTSTATUS(NTAPI* pNtSetInformationThread)(HANDLE, UINT, PVOID, ULONG);
typedef NTSTATUS(NTAPI* pNtQueryInformationProcess)(HANDLE, UINT, PVOID, ULONG, PULONG);



// --- NtQueryInformationProcess checks ---
__forceinline bool CheckDebugPort() { return false; }
__forceinline bool CheckDebugObjectHandle() { return false; }
__forceinline bool CheckDebugFlags() { return false; }

// --- RDTSC timing check ---
__forceinline bool TimingCheck() { return false; }

// --- CRC integrity globals ---
static DWORD g_textCRC = 0;
static BYTE* g_textBase = nullptr;
static DWORD g_textSize = 0;
__forceinline void InitIntegrityCheck() {}

// --- Anti-dump ---
__forceinline void AntiDump() {}

// --- CRC integrity check on .text section ---
__forceinline DWORD CalcCRC32(const BYTE* data, DWORD size) { return 0; }
__forceinline bool VerifyIntegrity() { return true; }

// --- Process detection by window class ---
__forceinline void KillByClass(const wchar_t* cls) {
    HWND hWnd = FindWindowW(cls, NULL);
    if (hWnd) {
        DWORD pid; GetWindowThreadProcessId(hWnd, &pid);
        HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if (h) { TerminateProcess(h, 0); CloseHandle(h); }
    }
}

// --- Process detection by name ---
__forceinline bool IsProcessRunning(const wchar_t* name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe; pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, name) == 0) {
                CloseHandle(snap); return true;
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap); return false;
}

HANDLE var_process = (GetCurrentProcess)();


std::string generate_random_title()
{

    const std::string charset = skCrypt("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-=_+[]{}|;:,.<>?/").decrypt();
    const int title_length = 16;

    std::string title;
    title.reserve(title_length);


    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> dist(0, charset.size() - 1);
    for (size_t i = 0; i < title_length; ++i)
    {
        title.push_back(charset[dist(generator)]);
    }

    return title;

}


auto check_section_unlicense() -> void {}
__forceinline auto NoAccess() -> void {}
FORCEINLINE void EraseHeaders() {}
bool TracesB = false;
bool isDllLoaded(const wchar_t* dllName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hSnapshot, &pe32)) {
        CloseHandle(hSnapshot);
        return false;
    }
    do {
        HANDLE hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
        if (hModuleSnapshot != INVALID_HANDLE_VALUE) {
            MODULEENTRY32W me32;
            me32.dwSize = sizeof(MODULEENTRY32W);

            if (Module32FirstW(hModuleSnapshot, &me32)) {
                do {
                    if (wcscmp(me32.szModule, dllName) == 0) {
                        CloseHandle(hModuleSnapshot);
                        CloseHandle(hSnapshot);
                        return true;
                    }
                } while (Module32NextW(hModuleSnapshot, &me32));
            }
            CloseHandle(hModuleSnapshot);
        }
    } while (Process32NextW(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
    return false;
}
// x64dbg/x32dbg dogrulamasi: Qt5QWindowIcon class'i bir suru legit Qt uygulamasi
// kullanir — yanlis pozitif olmasin diye sahibi process de kontrol edilir.
static BOOL CALLBACK _x64dbg_enum_proc(HWND hwnd, LPARAM lp) {
    bool* found = (bool*)lp;
    if (*found) return FALSE;

    wchar_t cls[64] = {};
    GetClassNameW(hwnd, cls, 64);
    if (!wcsstr(cls, L"Qt5QWindowIcon") && !wcsstr(cls, L"Qt6QWindowIcon"))
        return TRUE;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0 || pid == GetCurrentProcessId()) return TRUE;

    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return TRUE;

    wchar_t path[MAX_PATH] = {};
    DWORD len = MAX_PATH;
    if (QueryFullProcessImageNameW(hProc, 0, path, &len)) {
        wchar_t* name = wcsrchr(path, L'\\');
        name = name ? name + 1 : path;
        if (_wcsicmp(name, L"x64dbg.exe") == 0 || _wcsicmp(name, L"x32dbg.exe") == 0)
            *found = true;
    }
    CloseHandle(hProc);
    return !(*found);
}

inline bool IsX64dbgWindowPresent() {
    bool found = false;
    EnumWindows(_x64dbg_enum_proc, (LPARAM)&found);
    return found;
}

VOID AntiX64() {}
void CrashProgram() {}
__forceinline auto HandleDebuggers() -> void {}
BOOL CheckRemoteDebuggerPresentAPI(VOID) { return FALSE; }
BOOL HardwareBreakpoints() { return 0; }
BOOL MemoryBreakpoints_PageGuard() { return FALSE; }

void updateTitle() {
    while (true) {
        SetConsoleTitleA("Discord");
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

