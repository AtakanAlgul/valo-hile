#include <winsock2.h>
#include <ws2tcpip.h>
#include "include.h"
#include "../logger.hpp"
#include "Windows.h"
#include "iostream"
#include <stdio.h>
#include "Encrypt.hpp"
#include "Protection/vxlib.h"
#include "call_spoof.h"
#include "LAZYSHIT.h"
#include "LEZY.h"
#include <Shlwapi.h>
#include <ctime>
#include <random>
#include <conio.h>
#include <regex>    
#include <iphlpapi.h>
#include "base64.h"
#include <thread>
#include <chrono>
#include "Protection/security.h"
#include "shared.hpp"
#include "overlay/overlay_menu.hpp"
#include "overlay/overlay_render.hpp"
using namespace base64;
class ConsoleStreamBuf : public std::streambuf {
private:
    HANDLE m_hOut;
public:
    ConsoleStreamBuf() : m_hOut(INVALID_HANDLE_VALUE) {}
    void init(HANDLE h) { m_hOut = h; }

protected:
    virtual int_type overflow(int_type c) override {
        if (c != traits_type::eof() && m_hOut && m_hOut != INVALID_HANDLE_VALUE) {
            char ch = static_cast<char>(c);
            DWORD written = 0;
            WriteConsoleA(m_hOut, &ch, 1, &written, nullptr);
        }
        return c;
    }

    virtual std::streamsize xsputn(const char* s, std::streamsize n) override {
        if (n > 0 && m_hOut && m_hOut != INVALID_HANDLE_VALUE) {
            DWORD written = 0;
            WriteConsoleA(m_hOut, s, static_cast<DWORD>(n), &written, nullptr);
            return written;
        }
        return 0;
    }

    virtual int sync() override {
        return 0;
    }
};

class ConsoleInStreamBuf : public std::streambuf {
private:
    HANDLE m_hIn;
    char m_buf[512];
public:
    ConsoleInStreamBuf() : m_hIn(INVALID_HANDLE_VALUE) {}
    void init(HANDLE h) { m_hIn = h; }

protected:
    virtual int_type underflow() override {
        if (gptr() < egptr()) {
            return traits_type::to_int_type(*gptr());
        }
        if (!m_hIn || m_hIn == INVALID_HANDLE_VALUE) {
            return traits_type::eof();
        }
        DWORD read = 0;
        if (!ReadFile(m_hIn, m_buf, sizeof(m_buf), &read, nullptr) || read == 0) {
            return traits_type::eof();
        }
        setg(m_buf, m_buf, m_buf + read);
        return traits_type::to_int_type(*gptr());
    }
};

static ConsoleStreamBuf s_consoleBuf;
static ConsoleInStreamBuf s_consoleInBuf;

inline void ConsoleWrite(const char* str, size_t len = 0) {
    if (!str) return;
    if (len == 0) len = strlen(str);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut && hOut != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        WriteConsoleA(hOut, str, static_cast<DWORD>(len), &written, nullptr);
    }
}

void Clear();

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void SlowPrint(const string& str, int delay = 10) {
    for (char c : str) {
        cout << c << flush;
        Sleep(delay);
    }
}

void PrintBoxedMessage(const string& msg, int color = 7) {
    setColor(8);
    cout << skCrypt("  >> ").decrypt();
    setColor(color);
    cout << msg << endl;
    setColor(7);
}

void SecurityScanAnimation() {
    const char* stages[] = {
        "Initializing core...",
        "Bypassing integrity...",
        "Cleaning traces...",
        "Connecting to backend..."
    };
    for (int i = 0; i < 4; i++) {
        setColor(7);
        cout << "[+] " << stages[i] << endl;
        Sleep(800);
    }
}





using namespace std;
namespace fs = std::filesystem;

// AVERISYY removed — corrupting .text section conflicts with CRC integrity check
// and creates a detectable signature. AntiDump() handles anti-dump protection instead.
void AVERISYY() { /* no-op */ }

void type_text(const std::string& text, int delay_ms = 20) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

auto check_section_unlicenseX() -> void {}

void SetConsoleTransparency(int transparency) {
    Spoof_Address;
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
        SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hwnd, 0, transparency * 255 / 100, LWA_ALPHA);
    }
}

void Clear() {
    Spoof_Address;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;
    COORD homeCoord = { 0, 0 };
    FillConsoleOutputCharacterA(hConsole, ' ', cellCount, homeCoord, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoord, &written);
    SetConsoleCursorPosition(hConsole, homeCoord);
}

void Rename() {
    char szExeFileName[MAX_PATH];
    GetModuleFileNameA(NULL, szExeFileName, MAX_PATH);
    std::string path(szExeFileName);
    std::string exe = path.substr(path.find_last_of(skCrypt("\\").decrypt()) + 1);
    srand(static_cast<unsigned>(time(0)));
    char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char newname[20];
    int z = rand() % 8 + 8;
    for (int i = 0; i < z; i++) {
        char x = letters[rand() % 62];
        newname[i] = x;
    }
    newname[z] = '\0';
    strcat_s(newname, skCrypt(".exe").decrypt());

    rename(exe.c_str(), newname);
}

void WaitForConsoleEnter() {
    HANDLE hConIn = CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
    if (hConIn != INVALID_HANDLE_VALUE) {
        FlushConsoleInputBuffer(hConIn);
        INPUT_RECORD ir = {};
        DWORD read = 0;
        while (true) {
            if (ReadConsoleInputW(hConIn, &ir, 1, &read) && read > 0) {
                if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown &&
                    (ir.Event.KeyEvent.wVirtualKeyCode == VK_RETURN ||
                     ir.Event.KeyEvent.uChar.UnicodeChar == L'\r' ||
                     ir.Event.KeyEvent.uChar.UnicodeChar == L'\n')) {
                    break;
                }
            }
        }
        CloseHandle(hConIn);
    } else {
        while ((HIDE_ASM(GetAsyncKeyState)(VK_RETURN) & 0x8000) != 0) Sleep(20);
        while ((HIDE_ASM(GetAsyncKeyState)(VK_RETURN) & 0x8000) == 0) Sleep(20);
    }
}

void Averis() {

    Spoof_Address;

    LOG_STEP("[hpx] Driver kontrol ediliyor...");
    setColor(11); // Cyan
    std::cout << skCrypt("[*] Driver kontrol ediliyor...\n").decrypt();
    Sleep(300);

    if (driver::lexemvefind_driver()) {
        setColor(10); // Green
        std::cout << skCrypt("[+] Driver bulundu!\n").decrypt();
        std::cout << skCrypt("[+] Driver ile basariyla baglanti kuruldu.\n\n").decrypt();
        LOG_INFO("[hpx] Driver bulundu ve baglanti kuruldu.");
    }
    else {
        setColor(12); // Red
        std::cout << skCrypt("[-] Driver baglantisi kurulamadi!\n").decrypt();
        LOG_WARN("[hpx] Driver baglantisi kurulamadi! (Devam ediliyor)");
    }

    while (true) {
        setColor(14); // Yellow
        std::cout << skCrypt("[*] Lutfen Valorant'i acip lobiye girin ve bu konsolda [ENTER] tusuna basin...\n").decrypt();
        LOG_INFO("[hpx] Kullanicinin debug konsolunda ENTER tusuna basmasi bekleniyor...");

        WaitForConsoleEnter();

        setColor(11);
        std::cout << skCrypt("[*] Valorant araniyor...\n").decrypt();
        LOG_STEP("[hpx] ENTER basildi. Valorant sureci kontrol ediliyor (VALORANT-Win64-Shipping.exe)...");

        DWORD pid = driver::find_process(skCrypt(L"VALORANT-Win64-Shipping.exe").decrypt());
        if (pid) {
            setColor(10);
            std::cout << skCrypt("[+] Valorant bulundu!\n").decrypt();
            std::cout << skCrypt("[*] Hafiza baglantisi yapiliyor...\n").decrypt();
            Sleep(500);

            driver::processid = pid;
            baseee = driver::FindProcessBaseByPID(driver::processid);
            driver::process_cr3 = driver::SetCr3_Normal();

            LOG_INFO("[hpx] Valorant bulundu! PID: %lu, Base: 0x%llX, CR3: 0x%llX",
                driver::processid, baseee, driver::process_cr3);

            setColor(10);
            std::cout << skCrypt("[+] Kurulum tamamlandi, iyi oyunlar!\n\n").decrypt();
            Sleep(500);

            LOG_STEP("[hpx] game::AverisFind bellek okuma thread'i baslatiliyor...");
            HANDLE hFindThread = CreateThread(
                nullptr,
                0,
                (LPTHREAD_START_ROUTINE)game::AverisFind,
                nullptr,
                0,
                nullptr);
            if (hFindThread) {
                LOG_INFO("[hpx] AverisFind thread'i basariyla baslatildi (Handle: 0x%p)", hFindThread);
                CloseHandle(hFindThread);
            } else {
                LOG_WARN("[hpx] CreateThread (AverisFind) basarisiz! GetLastError: %lu", GetLastError());
            }
            break;
        }
        else {
            setColor(12); // Red
            std::cout << skCrypt("[-] Valorant bulunamadi! Oyunu actiktan sonra tekrar [ENTER] tusuna basin.\n\n").decrypt();
            LOG_WARN("[hpx] Valorant bulunamadi, kullanicidan tekrar ENTER bekleniyor...");
        }
    }
}

std::string tm_to_readable_time(tm ctx) {
    Spoof_Address;
    char buffer[80];

    HIDE_ASM(strftime)(buffer, sizeof(buffer), skCrypt("%a %m/%d/%y %H:%M:%S %Z").decrypt(), &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    Spoof_Address;
    auto cv = strtol(timestamp.c_str(), NULL, 10);

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    Spoof_Address;
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}

void check_host_name(int hostname) {
    Spoof_Address;
    if (hostname == -1) {
        perror(skCrypt("gethostname").decrypt());
        exit(EXIT_FAILURE);
    }
}

void check_host_entry(struct hostent* host_entry) {
    Spoof_Address;
    if (host_entry == nullptr) {
        perror(skCrypt("gethostbyname").decrypt());
        exit(EXIT_FAILURE);
    }
}




void DebugSelfX() {}
std::string GetPublicIPAddress() { return ""; }
__forceinline void AntiAttachX() {}

bool IsValidFormatmaw(const std::string& str) {
    if (str.size() != 19)
        return false;

    for (size_t i = 0; i < str.size(); ++i) {
        if (i % 5 == 4) {
            if (str[i] != '-')
                return false;
        }
        else {
            if (!isalnum(str[i]))
                return false;
        }
    }
    return true;
}

void SYAKABUBU() {


}

bool Averismatherffaker(const wchar_t* processName) {
    Spoof_Address;
    bool TANGINAMO = false;
    PROCESSENTRY32 KANTUTAN;
    KANTUTAN.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (Process32First(snapshot, &KANTUTAN)) {
        do {
            if (!_wcsicmp(KANTUTAN.szExeFile, processName)) {
                TANGINAMO = true;
                break;
            }
        } while (Process32Next(snapshot, &KANTUTAN));
    }

    CloseHandle(snapshot);
    return TANGINAMO;
}
__forceinline void KillProcessByName(const wchar_t* processName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return;
    PROCESSENTRY32W pe; pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, processName) == 0) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProc) { TerminateProcess(hProc, 0); CloseHandle(hProc); }
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
}

__forceinline void StopServiceNative(const wchar_t* svcName) {
    SC_HANDLE scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
    if (!scm) return;
    SC_HANDLE svc = OpenServiceW(scm, svcName, SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (svc) {
        SERVICE_STATUS ss;
        ControlService(svc, SERVICE_CONTROL_STOP, &ss);
        CloseServiceHandle(svc);
    }
    CloseServiceHandle(scm);
}
void AverisMafakers() {}

bool isProcessRunning(const wchar_t* processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry)) {


            if (!_wcsicmp(entry.szExeFile, processName))
                exists = true;
        }

    CloseHandle(snapshot);
    return exists;
}
bool AntiDebugB = true;

void checkurmomez2() {}


bool TerminateProcessWithModules2X(DWORD processID)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess == NULL)
    {
        return false;
    }

    if (TerminateProcess(hProcess, 0))
    {
        CloseHandle(hProcess);
        return true;
    }
    else
    {
        CloseHandle(hProcess);
        return false;
    }
}

__forceinline int SearchForDlls(DWORD processID)
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (NULL == hProcess)
        return 1;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                TCHAR dllFileName[MAX_PATH];
                if (PathFindFileName(szModName) != NULL)
                {
                    _tcscpy_s(dllFileName, MAX_PATH, PathFindFileName(szModName));
                }

                std::vector<const TCHAR*> blacklisted = { (skCrypt(_T("x64dbg.dll"))), skCrypt(_T("tcc64-64.dll")), skCrypt(_T("tcc64-64.dll")), skCrypt(_T("ScyllaHideX64DBGPlugin.dp64")) };
                for (const auto& targetDLL : blacklisted)
                {
                    if (_tcsstr(dllFileName, targetDLL) != NULL)
                    {
                        TerminateProcessWithModules2X(processID);
                        BlockInput(false);
                        setColor(2);
                        AVERISYY();
                        NoAccess(); EraseHeaders();

                    }
                }
            }
        }
    }
    CloseHandle(hProcess);

    return 0;
}
void PrintLoadedDllsX(DWORD dwProcessId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);

    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            wchar_t szModName[MAX_PATH];
            if (GetModuleFileNameExW(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(wchar_t))) {
                if (wcsstr(szModName, (skCrypt(L"x64\\imageformats"))) != nullptr)
                {
                    TerminateProcessWithModules2X(dwProcessId);
                    Sleep(2000);
                    BlockInput(false);
                    setColor(2);
                    AVERISYY();
                    NoAccess(); EraseHeaders();

                }
            }
        }
    }
    CloseHandle(hProcess);
}

__forceinline void BreakDebuggers()
{
    DWORD processes[1024];
    DWORD cbNeeded;

    if (EnumProcesses(processes, sizeof(processes), &cbNeeded))
    {
        unsigned int cProcesses = cbNeeded / sizeof(DWORD);

        for (unsigned int i = 0; i < cProcesses; i++)
        {
            SearchForDlls(processes[i]);
        }
    }
}

// SLIGHYRTAIEJI removed — writing to hosts file and leaving "Aeltrx" strings
// on disk is a massive forensic artifact. HyperHide check kept separately.
void SLIGHYRTAIEJI() {}
DWORD WINAPI AGFAWFRAUWFAIU(LPVOID lpParam) { return 0; }
void call(std::string msg) { std::cout << msg; }
VOID AntiAttachXB() {}
VOID AntiIDA() {}
bool IsCorrectTargetArchitecture(HANDLE hProc) {
    BOOL bTarget = FALSE;
    if (!IsWow64Process(hProc, &bTarget)) {
        exit(1);
    }
    BOOL bHost = FALSE;
    IsWow64Process(GetCurrentProcess(), &bHost);
    return (bTarget == bHost);
}

DWORD GetProcessIdByName(wchar_t* name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (_wcsicmp(entry.szExeFile, name) == 0) {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}

bool IsSuspiciousMemoryAccessDetected(const void* targetAddress, const size_t bufferSize) {
    DWORD oldProtect;
    if (VirtualProtect(const_cast<void*>(targetAddress), bufferSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        memset(const_cast<void*>(targetAddress), 0, bufferSize);
        VirtualProtect(const_cast<void*>(targetAddress), bufferSize, oldProtect, &oldProtect);

        if (IsBadReadPtr(targetAddress, bufferSize)) {
            return true;
        }
    }
    return false;
}


VOID AntiSuspendX() {}
VOID ErasePEHeaderFromMemory() {}
VOID Anti64() {}
VOID AntiPH() {}
VOID AntiDH() {}
void AntiCE() {}
VOID Filesize(DWORD min, DWORD max) {}
void DOALLNIGGAS() {}




bool IsAdmin() {

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdminGroup;
    BOOL bResult = (AllocateAndInitializeSid)(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdminGroup);

    if (!bResult) {
        return false;
    }

    BOOL isAdmin = FALSE;
    bResult = (CheckTokenMembership)(NULL, AdminGroup, &isAdmin);

    if (!bResult) {
        (FreeSid)(AdminGroup);
        return false;
    }

    (FreeSid)(AdminGroup);
    return isAdmin == TRUE;
}

std::string grabHarddrive() {
    HANDLE h = CreateFileW(skCrypt(L"\\\\.\\PhysicalDrive0").decrypt(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (h == INVALID_HANDLE_VALUE) return {};

    std::unique_ptr<std::remove_pointer<HANDLE>::type, void(*)(HANDLE)> hDevice{ h, [](HANDLE handle) {CloseHandle(handle); } };

    STORAGE_PROPERTY_QUERY storagePropertyQuery{};
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;

    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader{};

    DWORD dwBytesReturned = 0;
    if (!DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &dwBytesReturned, NULL))
        return {};

    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    std::unique_ptr<BYTE[]> pOutBuffer{ new BYTE[dwOutBufferSize]{} };

    if (!DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        pOutBuffer.get(), dwOutBufferSize, &dwBytesReturned, NULL))
        return {};

    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(pOutBuffer.get());
    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
    if (dwSerialNumberOffset == 0) return {};
    const char* serialNumber = reinterpret_cast<const char*>(pOutBuffer.get() + dwSerialNumberOffset);
    return serialNumber;
}

string ihateniggerslikezeker;



bool WINAPI HideThread(const HANDLE hThread) noexcept
{
    __try {

        using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE ThreadHandle, UINT ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
        const auto NtSetInformationThread{ reinterpret_cast<FnSetInformationThread>((GetProcAddress)((GetModuleHandleW)(skCrypt(L"ntdll.dll").decrypt()), skCrypt("NtSetInformationThread").decrypt()))};

        if (!NtSetInformationThread)
            return false;

        if (const auto status{ NtSetInformationThread(hThread, 0x11u, nullptr, 0ul) }; status == 0x00000000)
            return true;
    }
    __except (TRUE) {
        return false;
    }
    return false;
}

struct rgb_t { int r, g, b; };

inline rgb_t lerp_rgb(const rgb_t& a, const rgb_t& b, float t) {
    if (t <= 0.0f) return a;
    if (t >= 1.0f) return b;
    return {
        a.r + (int)((b.r - a.r) * t),
        a.g + (int)((b.g - a.g) * t),
        a.b + (int)((b.b - a.b) * t)
    };
}

inline float smooth_step(float t) {
    if (t <= 0.0f) return 0.0f;
    if (t >= 1.0f) return 1.0f;
    return t * t * (3.0f - 2.0f * t);
}



    template<typename... Args>
    inline void print23(const char* format, Args... args) {
        static std::mutex print_mutex;
        std::lock_guard<std::mutex> lock(print_mutex);
        // Purple to Pink gradient
        static constexpr rgb_t k_grad_a = { 108, 0, 255 };
        static constexpr rgb_t k_grad_b = { 190, 0, 255 };
        static constexpr rgb_t k_grad_c = { 255, 0, 190 };

        std::time_t now = std::time(nullptr);
        std::tm local_tm{};
        localtime_s(&local_tm, &now);
        char ts[32] = {};
        std::strftime(ts, sizeof(ts), "%H:%M:%S", &local_tm);

        char msg[4096];
        int n = snprintf(msg, sizeof(msg), format, args...);
        if (n < 0 || n >= (int)sizeof(msg)) {
            std::string out;
            const std::string prefix = std::string("[ ") + ts + " ] [ hpx ] -> ";
            const size_t total = prefix.size();
            for (size_t i = 0; i < total; ++i) {
                float t = (total > 1) ? (float)i / (float)(total - 1) : 0.0f;
                rgb_t c = {};
                if (t < 0.5f) {
                    c = lerp_rgb(k_grad_a, k_grad_b, smooth_step(t * 2.0f));
                }
                else {
                    c = lerp_rgb(k_grad_b, k_grad_c, smooth_step((t - 0.5f) * 2.0f));
                }
                char colBuf[32];
                snprintf(colBuf, sizeof(colBuf), "\x1b[38;2;%d;%d;%dm%c", c.r, c.g, c.b, prefix[i]);
                out += colBuf;
            }
            char rawBuf[2048];
            snprintf(rawBuf, sizeof(rawBuf), format, args...);
            out += rawBuf;
            out += "\x1b[0m\n";
            ConsoleWrite(out.c_str(), out.size());
            return;
        }

        size_t len = strlen(msg);
        while (len && (msg[len - 1] == '\n' || msg[len - 1] == '\r')) msg[--len] = '\0';

        std::string out;
            const std::string prefix = std::string("[ ") + ts + " ] [ hpx ] -> ";
        const size_t total = prefix.size();
        for (size_t i = 0; i < total; ++i) {
            float t = (total > 1) ? (float)i / (float)(total - 1) : 0.0f;
            rgb_t c = {};
            if (t < 0.5f) {
                c = lerp_rgb(k_grad_a, k_grad_b, smooth_step(t * 2.0f));
            }
            else {
                c = lerp_rgb(k_grad_b, k_grad_c, smooth_step((t - 0.5f) * 2.0f));
            }
            char colBuf[32];
            snprintf(colBuf, sizeof(colBuf), "\x1b[38;2;%d;%d;%dm%c", c.r, c.g, c.b, prefix[i]);
            out += colBuf;
        }
        out += "\x1b[97m";
        out += msg;
        out += "\x1b[0m\n";
        ConsoleWrite(out.c_str(), out.size());
    }

long crash_handler(EXCEPTION_POINTERS* exception_pointers) {
    const auto* context = exception_pointers->ContextRecord;
    char message[1024];
    sprintf_s(message,
        ("Oops! Something went wrong!\n\n"
            "The service encountered an unexpected error and needs to close.\n\n"
            "Quick fixes to try:\n"
            "  • Restart the service\n"
            "  • Rollback recent updates to the service\n"
            "  • Check if your antivirus is interfering\n\n"
            "Still having trouble? We're here to help!\n"
            "Contact support through the tickets section.\n\n"
            "Crash Details:\n"
            "Build: %s %s\n"
            "Error: 0x%08X at %p\n"
            "Registers: RSP=%016llX RDI=%016llX\n"
            "           RSI=%016llX RBX=%016llX\n"
            "           RDX=%016llX RCX=%016llX\n"
            "           RAX=%016llX RBP=%016llX"),
        __DATE__, __TIME__,
        exception_pointers->ExceptionRecord->ExceptionCode,
        exception_pointers->ExceptionRecord->ExceptionAddress,
        context->Rsp, context->Rdi,
        context->Rsi, context->Rbx,
        context->Rdx, context->Rcx,
        context->Rax, context->Rbp
    );
    terminate();
    print23(("caught exception (0x%x)"),
        exception_pointers->ExceptionRecord->ExceptionCode);
    MessageBoxA(0, message, "unexpected Error", MB_ICONERROR | MB_OK);
    return EXCEPTION_EXECUTE_HANDLER;
}

bool unload_handler(std::uint32_t signal) {
    terminate();
    return true;
}

void initialize() {
    auto std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(std_handle, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(std_handle, mode);

    SetUnhandledExceptionFilter(crash_handler);
    SetConsoleCtrlHandler(
        reinterpret_cast<PHANDLER_ROUTINE>(unload_handler),
        true
    );
}

static void SelfIntegrityCheck() {}

// ── Window name guard: constantly scans top-level window titles, class names
//    and owner exe names for reverse-engineering / analysis tools ─────────────
namespace wnguard {

struct GuardKeyword {
    std::wstring low;    // lowercase raw keyword
    std::wstring norm;   // alnum-only lowercase keyword
    bool         isShort;
};

inline wchar_t lowc(wchar_t c) {
    return (c >= L'A' && c <= L'Z') ? (wchar_t)(c + (L'a' - L'A')) : c;
}
inline bool alnum(wchar_t c) {
    return (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9');
}

inline std::wstring wlower(std::wstring s) {
    for (auto& c : s) c = lowc(c);
    return s;
}
inline std::wstring wonly(const std::wstring& s) {
    std::wstring r;
    for (auto c : s) if (alnum(c)) r.push_back(lowc(c));
    return r;
}

inline bool hasword(const std::wstring& hay, const std::wstring& w) {
    if (w.empty()) return false;
    size_t p = 0;
    while ((p = hay.find(w, p)) != std::wstring::npos) {
        bool before = (p == 0) || !alnum(hay[p - 1]);
        size_t end = p + w.size();
        bool after = (end >= hay.size()) || !alnum(hay[end]);
        if (before && after) return true;
        p = end;
    }
    return false;
}

struct Ctx {
    const std::vector<GuardKeyword>* kws;
    bool* hit;
};

inline void build(std::vector<GuardKeyword>& kws) {
    const std::string raw[] = {
        xorstr_("cheatengine"), xorstr_("cheat engine"),
        xorstr_("cheatengine-x86_64"), xorstr_("cheatengine-x86_64-sse4-avx2"),
        xorstr_("x64dbg"), xorstr_("x32dbg"), xorstr_("ollydbg"), xorstr_("windbg"),
        xorstr_("ida"), xorstr_("ida64"), xorstr_("idaq"), xorstr_("idaq64"),
        xorstr_("idaw"), xorstr_("idaw64"), xorstr_("ida pro"), xorstr_("ida:"),
        xorstr_("scylla"), xorstr_("scylla_x64"), xorstr_("scylla_x86"),
        xorstr_("protection_id"), xorstr_("reshacker"), xorstr_("lordpe"),
        xorstr_("peid"), xorstr_("exeinfope"),
        xorstr_("process hacker"), xorstr_("processhacker"), xorstr_("processhacker2"), xorstr_("ph2"),
        xorstr_("procmon"), xorstr_("procmon64"),
        xorstr_("folderchangesview"), xorstr_("folder changes view"),
        xorstr_("wireshark"), xorstr_("fiddler"), xorstr_("charles"),
        xorstr_("httpdebugger"), xorstr_("http debugger"),
        xorstr_("dnspy"), xorstr_("de4dot"), xorstr_("dotpeek"), xorstr_("ilspy"), xorstr_("reflexil"),
        xorstr_("pestudio"), xorstr_("die"), xorstr_("exeinfo"), xorstr_("cff explorer"),
        xorstr_("vmmap"), xorstr_("rammap"), xorstr_("autoruns"), xorstr_("autorunsc"),
        xorstr_("api monitor"), xorstr_("apimonitor"), xorstr_("apimonitor-x86"), xorstr_("apimonitor-x64"),
        xorstr_("spy++"), xorstr_("spyxx"), xorstr_("spyxx_amd64"),
        xorstr_("regshot"), xorstr_("regshot-x64-ansi"),
        xorstr_("httptoolkit"), xorstr_("mitmproxy"), xorstr_("burpsuite"),
        xorstr_("ghidra"), xorstr_("radare2"), xorstr_("r2"), xorstr_("cutter"),
        xorstr_("binary ninja"), xorstr_("binaryninja"),
        xorstr_("hxd"), xorstr_("010editor"), xorstr_("hexworkshop"), xorstr_("winhex"),
        xorstr_("importrec"), xorstr_("imprec"), xorstr_("rebuildimports"),
        xorstr_("dumpit"), xorstr_("winpmem"), xorstr_("[elevated]"), xorstr_("x64netdumper"),
        xorstr_("gdb"), xorstr_("lldb"), xorstr_("immunitydebugger"), xorstr_("w32dasm"),
        xorstr_("edb"), xorstr_("div"), xorstr_("trw2000"), xorstr_("syser"), xorstr_("hopper"),
        xorstr_("frida"), xorstr_("frida-server"), xorstr_("drrun"), xorstr_("pin"),
        xorstr_("artmoney"), xorstr_("procdump"), xorstr_("procdump64"),
        xorstr_("procexp"), xorstr_("procexp64"), xorstr_("tcpview"), xorstr_("tcpview64"),
        xorstr_("cports"), xorstr_("filemon"), xorstr_("regmon"),
        xorstr_("volatility"), xorstr_("vol"), xorstr_("rekall"),
        xorstr_("ethereal"), xorstr_("tshark"), xorstr_("ettercap"), xorstr_("bettercap"),
        xorstr_("glasswire"), xorstr_("cain"), xorstr_("zenmap"), xorstr_("nmap"),
        xorstr_("snort"), xorstr_("suricata"), xorstr_("dsniff"), xorstr_("ngrep"),
        xorstr_("omnipeek"), xorstr_("capsa"), xorstr_("commview"), xorstr_("tcpflow"),
        xorstr_("prtg"), xorstr_("masscan"), xorstr_("zmap"), xorstr_("hping3"), xorstr_("iperf"),
        xorstr_("xxd"), xorstr_("bvi"), xorstr_("pd32"), xorstr_("sysdig")
    };
    for (const auto& k : raw) {
        std::wstring w;
        for (char c : k) w.push_back((wchar_t)(unsigned char)c);
        GuardKeyword g;
        g.low = wlower(w);
        g.norm = wonly(w);
        g.isShort = g.norm.size() < 6;
        kws.push_back(g);
    }
}

inline BOOL CALLBACK enumproc(HWND hwnd, LPARAM lp) {
    auto* ctx = (Ctx*)lp;
    if (!IsWindow(hwnd)) return TRUE;

    wchar_t title[512] = { 0 };
    wchar_t cls[256] = { 0 };
    GetWindowTextW(hwnd, title, 512);
    GetClassNameW(hwnd, cls, 256);

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0 || pid == GetCurrentProcessId()) return TRUE;

    std::wstring tLow = wlower(title), cLow = wlower(cls);
    std::wstring tNorm = wonly(tLow), cNorm = wonly(cLow);

    std::wstring pLow, pNorm;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProc) {
        wchar_t path[MAX_PATH] = { 0 };
        DWORD len = MAX_PATH;
        if (QueryFullProcessImageNameW(hProc, 0, path, &len)) {
            wchar_t* name = wcsrchr(path, L'\\');
            name = name ? name + 1 : path;
            pLow = wlower(name);
            if (pLow.size() > 4 && pLow.substr(pLow.size() - 4) == L".exe")
                pLow.erase(pLow.size() - 4);
            pNorm = wonly(pLow);
        }
        CloseHandle(hProc);
    }

    for (auto& kw : *ctx->kws) {
        bool nameHit = kw.isShort
            ? (hasword(tLow, kw.low) || hasword(cLow, kw.low))
            : (tNorm.find(kw.norm) != std::wstring::npos || cNorm.find(kw.norm) != std::wstring::npos);
        bool procHit = !pNorm.empty() && pNorm.find(kw.norm) != std::wstring::npos;
        if (nameHit && procHit) {
            HANDLE hKill = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
            if (hKill) { TerminateProcess(hKill, 0); CloseHandle(hKill); }
            *ctx->hit = true;
            return FALSE;
        }
    }
    return TRUE;
}

} // namespace wnguard

void WindowGuardThread() {}

void SetupDebugConsole() {
    if (GetConsoleWindow() == nullptr) {
        AllocConsole();
    }

    HANDLE hConOut = CreateFileA(
        "CONOUT$",
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );

    if (hConOut == INVALID_HANDLE_VALUE) {
        hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    } else {
        SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
        SetStdHandle(STD_ERROR_HANDLE, hConOut);
    }

    HANDLE hConIn = CreateFileA(
        "CONIN$",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );
    if (hConIn != INVALID_HANDLE_VALUE) {
        SetStdHandle(STD_INPUT_HANDLE, hConIn);
        s_consoleInBuf.init(hConIn);
        std::cin.rdbuf(&s_consoleInBuf);
        std::cin.clear();
    }

    // Host (Discord Node.js) fd'lerini bozmadan std::cout ve std::cerr'i WriteConsoleA buffer'ina bagla
    s_consoleBuf.init(hConOut);
    std::cout.rdbuf(&s_consoleBuf);
    std::cerr.rdbuf(&s_consoleBuf);
    std::cout.clear();
    std::cerr.clear();
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    SetConsoleTitleA("hpx");

    DWORD dwMode = 0;
    if (GetConsoleMode(hConOut, &dwMode))
        SetConsoleMode(hConOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT);
}

static SharedESPData s_local_esp_data = {};

void InitSharedData() {
    g_esp_data = &s_local_esp_data;
    ZeroMemory(g_esp_data, sizeof(SharedESPData));
    g_esp_data->overlay_connected = true;

    // Varsayilan overlay ayarlari
    g_esp_data->settings.box2d = false;
    g_esp_data->settings.corner = true;
    g_esp_data->settings.box3d = false;
    g_esp_data->settings.sk3let0n = true;
    g_esp_data->settings.h3althbar = true;
    g_esp_data->settings.headb0x = false;
    g_esp_data->settings.snapline = false;
    g_esp_data->settings.vischeck = false;
    g_esp_data->settings.esp_thickness = 1.0f;
    g_esp_data->settings.vis_r = 1.0f; g_esp_data->settings.vis_g = 0.0f; g_esp_data->settings.vis_b = 0.0f; g_esp_data->settings.vis_a = 1.0f;
    g_esp_data->settings.invis_r = 1.0f; g_esp_data->settings.invis_g = 1.0f; g_esp_data->settings.invis_b = 1.0f; g_esp_data->settings.invis_a = 1.0f;

    g_esp_data->settings.a1mbot = true;
    g_esp_data->settings.a1m_v1sh_ch3ck = true;
    g_esp_data->settings.reco1l_contr0l = true;
    g_esp_data->settings.draw_f0v = true;
    g_esp_data->settings.a1m_sm00th = 10.0f;
    g_esp_data->settings.a1m_f0v = 40.0f;
    g_esp_data->settings.a1m_b0ne = 0;
    g_esp_data->settings.a1m_k3y = 0x01;
}

DWORD WINAPI MainDllThread(LPVOID lpParam) {
    LOG_STEP("[MainDllThread] Baslatildi.");
    SetupDebugConsole();
    LOG_STEP("[MainDllThread] Debug konsol ayarlandi.");
    InitSharedData();
    game::SyncSharedSettingsToConfig();
    LOG_STEP("[MainDllThread] Shared data hazirlandi ve ayarlara esitlendi.");

    Spoof_Address;

    auto updatetitle = HIDE_ASM(updateTitle);
    std::thread titleThread((updatetitle));
    titleThread.detach();
    LOG_STEP("[MainDllThread] Title updater thread baslatildi.");

    VL_OBFUSCATION_BEGIN;

    initialize();
    LOG_STEP("[MainDllThread] initialize() tamamlandi.");

    extern int g_daysLeftGlobal;
    g_daysLeftGlobal = 9999;

    // Yeni overlay'e ESP cizim callback'ini bagla
    renderer::g_render_callback = []() {
        game::SyncSharedSettingsToConfig();
        game::render_players();
    };

    // Debug konsolunda ENTER beklenip Valorant bulunduktan sonra overlay baslatilir
    LOG_STEP("[MainDllThread] hpx baslatiliyor (Debug konsolunda ENTER bekleniyor)...");
    HIDE_ASM(Averis)();

    // YENİ OVERLAY: C:\Users\mm\Desktop\exaa\overlay baslatiliyor
    LOG_STEP("[MainDllThread] Yeni overlay baslatiliyor (renderer::hook_present)...");
    renderer::hook_present();

    LOG_STEP("[MainDllThread] Yeni overlay render dongusune giriliyor (renderer::render_loop)...");
    renderer::render_loop();

    LOG_STEP("[MainDllThread] Yeni overlay temizleniyor (renderer::unhook_present)...");
    renderer::unhook_present();

    return 0;
}

LONG WINAPI CrashHandler(PEXCEPTION_POINTERS pExceptionInfo);

// Thread pool wrapper: MainDllThread'i OS thread pool üzerinden çalıştırır.
// Thread start address = ntdll!TppWorkerThread (backed, meşru modül).
// Anti-cheat NtQueryInformationThread(ThreadQuerySetWin32StartAddress) çağırdığında
// backed bir adres görür — tespit edilmez.
static HMODULE s_dll_module = nullptr;

static DWORD WINAPI PooledMainEntry(LPVOID) {
    return MainDllThread(s_dll_module);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        Logger::Init(hModule);
        LOG_INFO("=== DllMain: DLL_PROCESS_ATTACH ===");

        // Manual Map ile yüklendiğinde modül PEB->Ldr listesinde olmadığından
        // yalnızca PEB->Ldr'de kayıtlıysa DisableThreadLibraryCalls çağır.
        HMODULE hRealMod = nullptr;
        if (GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCWSTR>(&DllMain),
                &hRealMod) && hRealMod) {
            DisableThreadLibraryCalls(hRealMod);
        }

        s_dll_module = hModule;
        HANDLE hThread = CreateThread(nullptr, 0, MainDllThread, hModule, 0, nullptr);
        if (hThread) {
            LOG_INFO("[DllMain] MainDllThread olusturuldu (Handle: 0x%p)", hThread);
            CloseHandle(hThread);
        } else {
            LOG_ERROR("[DllMain] CreateThread basarisiz! GetLastError: %lu", GetLastError());
        }
    } else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        LOG_INFO("=== DllMain: DLL_PROCESS_DETACH ===");
    }
    return TRUE;
}