#pragma once
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <tlhelp32.h>

namespace Logger {

    static const char* LOG_PATH   = "C:\\Users\\mm\\Desktop\\exaa\\x64\\Release\\error_log.txt";
    static const char* CRASH_PATH = "C:\\Users\\mm\\Desktop\\exaa\\x64\\Release\\crash.txt";

    static CRITICAL_SECTION g_cs;
    static bool g_initialized = false;
    static HMODULE g_dllModule = nullptr;

    inline void EnsureDirectoryExists() {
        CreateDirectoryA("C:\\Users\\mm\\Desktop\\exaa\\x64", NULL);
        CreateDirectoryA("C:\\Users\\mm\\Desktop\\exaa\\x64\\Release", NULL);
    }

    inline void WriteRaw(const char* filepath, const std::string& text) {
        EnsureDirectoryExists();
        HANDLE hFile = CreateFileA(
            filepath,
            FILE_APPEND_DATA,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD written = 0;
            WriteFile(hFile, text.data(), (DWORD)text.size(), &written, nullptr);
            FlushFileBuffers(hFile);
            CloseHandle(hFile);
        }
    }

    inline std::string GetTimestamp() {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char buf[64];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        return std::string(buf);
    }

    inline void Log(const char* level, const char* fmt, ...) {
        char msgBuf[2048];
        va_list args;
        va_start(args, fmt);
        vsnprintf(msgBuf, sizeof(msgBuf), fmt, args);
        va_end(args);

        std::string timeStr = GetTimestamp();
        DWORD tid = GetCurrentThreadId();

        char lineBuf[2560];
        snprintf(lineBuf, sizeof(lineBuf), "[%s] [TID:%05lu] [%-8s] %s\n",
            timeStr.c_str(), tid, level, msgBuf);

        if (g_initialized) {
            EnterCriticalSection(&g_cs);
        }

        WriteRaw(LOG_PATH, lineBuf);

        // Ayrıca konsol veya debugger varsa ilet
        OutputDebugStringA(lineBuf);

        if (g_initialized) {
            LeaveCriticalSection(&g_cs);
        }
    }

    inline const char* ExceptionCodeToString(DWORD code) {
        switch (code) {
        case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION (0xC0000005)";
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED (0xC000008C)";
        case EXCEPTION_BREAKPOINT:                return "EXCEPTION_BREAKPOINT (0x80000003)";
        case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT (0x80000002)";
        case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND (0xC000008D)";
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO (0xC000008E)";
        case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT (0xC000008F)";
        case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION (0xC0000090)";
        case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW (0xC0000091)";
        case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK (0xC0000092)";
        case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW (0xC0000093)";
        case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION (0xC000001D)";
        case EXCEPTION_IN_PAGE_ERROR:            return "EXCEPTION_IN_PAGE_ERROR (0xC0000006)";
        case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO (0xC0000094)";
        case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW (0xC0000095)";
        case EXCEPTION_INVALID_DISPOSITION:      return "EXCEPTION_INVALID_DISPOSITION (0xC0000026)";
        case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION (0xC0000025)";
        case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION (0xC0000096)";
        case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP (0x80000004)";
        case EXCEPTION_STACK_OVERFLOW:           return "EXCEPTION_STACK_OVERFLOW (0xC00000FD)";
        case 0xE06D7363:                         return "MSVC_C++_EXCEPTION (0xE06D7363)";
        default:                                 return "UNKNOWN_EXCEPTION";
        }
    }

    inline bool SafeReadMemory(const void* addr, uintptr_t* outVal) {
        __try {
            *outVal = *(const uintptr_t*)addr;
            return true;
        } __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline void LogCrash(PEXCEPTION_POINTERS pExceptionInfo, const char* source = "VectoredExceptionHandler") {
        if (!pExceptionInfo || !pExceptionInfo->ExceptionRecord || !pExceptionInfo->ContextRecord)
            return;

        auto rec = pExceptionInfo->ExceptionRecord;
        auto ctx = pExceptionInfo->ContextRecord;

        std::stringstream ss;
        ss << "\n============================== [CRASH REPORT] ==============================\n";
        ss << "Source:       " << source << "\n";
        ss << "Time:         " << GetTimestamp() << "\n";
        ss << "Thread ID:    " << GetCurrentThreadId() << "\n";
        ss << "Process ID:   " << GetCurrentProcessId() << "\n";

        char procPath[MAX_PATH] = "Unknown";
        GetModuleFileNameA(NULL, procPath, MAX_PATH);
        ss << "Host Process: " << procPath << "\n";

        char dllPath[MAX_PATH] = "Unknown";
        if (g_dllModule) {
            GetModuleFileNameA(g_dllModule, dllPath, MAX_PATH);
            ss << "DLL Path:     " << dllPath << " (Base: 0x" << std::hex << (uintptr_t)g_dllModule << std::dec << ")\n";
        }

        ss << "Exception:    0x" << std::hex << rec->ExceptionCode << " -> " << ExceptionCodeToString(rec->ExceptionCode) << std::dec << "\n";
        ss << "Fault Addr:   0x" << std::hex << (uintptr_t)rec->ExceptionAddress << std::dec << "\n";

        // Access violation detayları
        if (rec->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && rec->NumberParameters >= 2) {
            ULONG_PTR op = rec->ExceptionInformation[0];
            ULONG_PTR addr = rec->ExceptionInformation[1];
            const char* opStr = (op == 0) ? "READ" : ((op == 1) ? "WRITE" : "EXECUTE (DEP)");
            ss << "Access Type:  Attempted to " << opStr << " invalid memory address 0x" << std::hex << addr << std::dec << "\n";
        }

        // Fault modülü bul
        HMODULE hMod = nullptr;
        if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR)rec->ExceptionAddress, &hMod) && hMod) {
            char modName[MAX_PATH] = "Unknown";
            GetModuleFileNameA(hMod, modName, MAX_PATH);
            uintptr_t offset = (uintptr_t)rec->ExceptionAddress - (uintptr_t)hMod;
            ss << "Fault Module: " << modName << "\n";
            ss << "Module Base:  0x" << std::hex << (uintptr_t)hMod << "\n";
            ss << "Offset:       0x" << std::hex << offset << std::dec << "\n";
        } else {
            ss << "Fault Module: [Not inside any known module / Dynamic Code]\n";
        }

        // CPU Register'ları
        ss << "\n--- CPU REGISTERS (x64) ---\n";
        ss << "RAX: 0x" << std::hex << ctx->Rax << "  RBX: 0x" << ctx->Rbx << "  RCX: 0x" << ctx->Rcx << "  RDX: 0x" << ctx->Rdx << "\n";
        ss << "RSI: 0x" << std::hex << ctx->Rsi << "  RDI: 0x" << ctx->Rdi << "  RBP: 0x" << ctx->Rbp << "  RSP: 0x" << ctx->Rsp << "\n";
        ss << "RIP: 0x" << std::hex << ctx->Rip << "  EFLAGS: 0x" << ctx->EFlags << "\n";
        ss << "R8:  0x" << std::hex << ctx->R8  << "  R9:  0x" << ctx->R9  << "  R10: 0x" << ctx->R10 << "  R11: 0x" << ctx->R11 << "\n";
        ss << "R12: 0x" << std::hex << ctx->R12 << "  R13: 0x" << ctx->R13 << "  R14: 0x" << ctx->R14 << "  R15: 0x" << ctx->R15 << std::dec << "\n";

        // Call Stack Backtrace
        ss << "\n--- CALL STACK BACKTRACE ---\n";
        void* backtrace[64];
        WORD frames = RtlCaptureStackBackTrace(0, 64, backtrace, nullptr);
        for (WORD i = 0; i < frames; ++i) {
            void* frameAddr = backtrace[i];
            HMODULE frameMod = nullptr;
            char frameModName[MAX_PATH] = "Unknown";
            uintptr_t frameOffset = 0;
            if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                (LPCSTR)frameAddr, &frameMod) && frameMod) {
                GetModuleFileNameA(frameMod, frameModName, MAX_PATH);
                char* slash = strrchr(frameModName, '\\');
                const char* shortName = slash ? slash + 1 : frameModName;
                frameOffset = (uintptr_t)frameAddr - (uintptr_t)frameMod;
                ss << "  #" << i << "  0x" << std::hex << (uintptr_t)frameAddr << " [" << shortName << " + 0x" << frameOffset << "]" << std::dec << "\n";
            } else {
                ss << "  #" << i << "  0x" << std::hex << (uintptr_t)frameAddr << " [Unknown/Dynamic]" << std::dec << "\n";
            }
        }

        // RSP Stack Memory Preview (Top 16 QWORDs)
        ss << "\n--- STACK PREVIEW (RSP) ---\n";
        uintptr_t* pStack = (uintptr_t*)ctx->Rsp;
        for (int i = 0; i < 16; ++i) {
            uintptr_t val = 0;
            if (SafeReadMemory(pStack + i, &val)) {
                ss << "  [RSP+" << std::hex << (i * 8) << "] = 0x" << val << std::dec << "\n";
            } else {
                ss << "  [RSP+" << std::hex << (i * 8) << "] = <Inaccessible Memory>\n" << std::dec;
                break;
            }
        }

        ss << "============================================================================\n\n";

        std::string report = ss.str();

        // Hem error_log.txt hem de crash.txt dosyasına yaz ve diske flush et
        WriteRaw(LOG_PATH, report);
        WriteRaw(CRASH_PATH, report);
        OutputDebugStringA(report.c_str());
    }

    inline LONG WINAPI GlobalVectoredCrashHandler(PEXCEPTION_POINTERS pExceptionInfo) {
        if (!pExceptionInfo || !pExceptionInfo->ExceptionRecord)
            return EXCEPTION_CONTINUE_SEARCH;

        DWORD code = pExceptionInfo->ExceptionRecord->ExceptionCode;

        // Normal/zararsız debug veya iç istisnaları atla
        if (code == EXCEPTION_BREAKPOINT ||
            code == EXCEPTION_SINGLE_STEP ||
            code == 0x40010006 || // DBG_PRINTEXCEPTION_C
            code == 0x406D1388 || // Thread naming
            code == 0x000006BA)   // RPC_S_SERVER_UNAVAILABLE (Discord iç COM çağrıları)
        {
            return EXCEPTION_CONTINUE_SEARCH;
        }

        // Yalnızca kritik hata/çökme istisnalarını yakala
        if ((code & 0xC0000000) == 0xC0000000 || code == 0xE06D7363) {
            static volatile LONG s_inCrash = 0;
            if (InterlockedCompareExchange(&s_inCrash, 1, 0) == 0) {
                LogCrash(pExceptionInfo, "VectoredExceptionHandler");
            }
        }

        return EXCEPTION_CONTINUE_SEARCH;
    }

    inline LONG WINAPI GlobalUnhandledCrashHandler(PEXCEPTION_POINTERS pExceptionInfo) {
        LogCrash(pExceptionInfo, "UnhandledExceptionFilter");
        return EXCEPTION_EXECUTE_HANDLER;
    }

    inline void Init(HMODULE hMod) {
        if (g_initialized) return;
        g_dllModule = hMod;
        InitializeCriticalSection(&g_cs);
        g_initialized = true;

        EnsureDirectoryExists();

        // Exception handler'ları kur
        AddVectoredExceptionHandler(1, GlobalVectoredCrashHandler);
        SetUnhandledExceptionFilter(GlobalUnhandledCrashHandler);

        char procPath[MAX_PATH] = "Unknown";
        GetModuleFileNameA(NULL, procPath, MAX_PATH);

        char dllPath[MAX_PATH] = "Unknown";
        if (hMod) GetModuleFileNameA(hMod, dllPath, MAX_PATH);

        std::stringstream ss;
        ss << "\n############################################################################\n";
        ss << "#                   DETAILED LOG INITIALIZED                              #\n";
        ss << "############################################################################\n";
        ss << "Session Start:   " << GetTimestamp() << "\n";
        ss << "Host Process:    " << procPath << " (PID: " << GetCurrentProcessId() << ")\n";
        ss << "Injected DLL:    " << dllPath << " (Base: 0x" << std::hex << (uintptr_t)hMod << std::dec << ")\n";
        ss << "Current TID:     " << GetCurrentThreadId() << "\n";
        ss << "Command Line:    " << GetCommandLineA() << "\n";
        ss << "Log Path:        " << LOG_PATH << "\n";
        ss << "Crash Path:      " << CRASH_PATH << "\n";
        ss << "############################################################################\n\n";

        WriteRaw(LOG_PATH, ss.str());
    }

} // namespace Logger

#define LOG_INFO(fmt, ...)     Logger::Log("INFO", fmt, ##__VA_ARGS__)
#define LOG_STEP(fmt, ...)     Logger::Log("STEP", fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)     Logger::Log("WARN", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)    Logger::Log("ERROR", fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) Logger::Log("CRITICAL", fmt, ##__VA_ARGS__)

#define LOG_EXIT(code) do { \
    LOG_CRITICAL("[FATAL EXIT CALL] exit(%d) cagrildi! Dosya: %s, Satir: %d (Host Process Kapatiliyor!)", (code), __FILE__, __LINE__); \
    exit(code); \
} while(0)
