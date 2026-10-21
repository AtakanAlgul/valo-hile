// overlay_entry.cpp — overlay.dll / discord_overlay_sdk_x64.dll spoof
// Gerçek discord_overlay_sdk_x64.dll export ABI'si ile birebir uyumlu.
// DiscordHook64 bu DLL'i yükleyip InitDxgi / OnPresent vb. çağırır;
// biz de pipe'ı canlı tutarak Discord'un EBADF hatasını önlüyoruz.

#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "overlay_render.hpp"
#include "overlay_menu.hpp"
#include "imgui.h"
#include "ipc_client.hpp"
#include <thread>
#include <atomic>
#include <string>

#include "../logger.hpp"

// ─── DISCORD OVERLAY SDK — GERÇEĞİ İLE BİREBİR EXPORT İMZALARI ─────────────
// discord_overlay_sdk_x64.dll'nin gerçek export listesi:
//   CharEvent, ForwardMessage, ImeCancelComposition, ImeCommitText,
//   ImeSetComposition, InitD3d12, InitDxgi, KeyEvent, MouseButtonEvent,
//   MouseMotionEvent, OnPresent, PointInsideClickZone,
//   SetImeCompositionRangeCallback, SetImeSelectionBoundsCallback
//
// DiscordHook64 -> InitDxgi(pSwapChain, hwnd, pipeName)
//               -> OnPresent(pSwapChain, syncInterval, flags)
//
// Pipe bağlantısını canlı tutmazsan Discord main process'i EBADF atar.
// ─────────────────────────────────────────────────────────────────────────────

namespace {
    // Pipe canlı-tutma thread'i
    static std::atomic<bool>  s_pipe_running{ false };
    static HANDLE             s_pipe_handle  = INVALID_HANDLE_VALUE;
    static std::string        s_pipe_name;

    static DWORD WINAPI PipeKeepaliveThread(LPVOID) {
        // DiscordHook64'ün oluşturduğu pipe'a bağlan
        for (int retry = 0; retry < 20 && s_pipe_running; ++retry) {
            HANDLE h = CreateFileA(
                s_pipe_name.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0, nullptr, OPEN_EXISTING,
                FILE_FLAG_OVERLAPPED, nullptr);

            if (h != INVALID_HANDLE_VALUE) {
                s_pipe_handle = h;
                LOG_INFO("[DiscordSDK] Pipe baglantisi kuruldu: %s", s_pipe_name.c_str());
                break;
            }

            DWORD gle = GetLastError();
            if (gle == ERROR_PIPE_BUSY) {
                WaitNamedPipeA(s_pipe_name.c_str(), 500);
            } else {
                Sleep(200);
            }
        }

        // Pipe açıkken boş mesaj döngüsü — Discord'un yazmasına izin ver
        const DWORD BUF = 4096;
        char buf[BUF];
        while (s_pipe_running && s_pipe_handle != INVALID_HANDLE_VALUE) {
            DWORD read = 0;
            OVERLAPPED ov = {};
            ov.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
            BOOL ok = ReadFile(s_pipe_handle, buf, BUF, &read, &ov);
            if (!ok && GetLastError() == ERROR_IO_PENDING) {
                // 500 ms bekle; timeout'ta döngüye dön
                WaitForSingleObject(ov.hEvent, 500);
                GetOverlappedResult(s_pipe_handle, &ov, &read, FALSE);
            }
            if (ov.hEvent) CloseHandle(ov.hEvent);

            if (read > 0) {
                // Minimal ack: 4 byte null yanıt
                DWORD written = 0;
                BYTE ack[4] = {};
                WriteFile(s_pipe_handle, ack, sizeof(ack), &written, nullptr);
            }
        }

        if (s_pipe_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(s_pipe_handle);
            s_pipe_handle = INVALID_HANDLE_VALUE;
        }
        return 0;
    }

    static void StartPipeKeepalive(const char* pipeName) {
        if (!pipeName || pipeName[0] == '\0') return;
        s_pipe_name    = pipeName;
        s_pipe_running = true;
        CloseHandle(CreateThread(nullptr, 0, PipeKeepaliveThread, nullptr, 0, nullptr));
    }
}

extern ImGuiKey ImGui_ImplWin32_KeyEventToImGuiKey(WPARAM wParam, LPARAM lParam);

// ─── EXPORTS — gerçek discord_overlay_sdk_x64.dll ile birebir ───────────────
extern "C" {

    // InitDxgi — DiscordHook64 tarafından DXGI swap chain ile çağrılır
    // Gerçek imza: HRESULT InitDxgi(IDXGISwapChain*, HWND, const char* pipeName)
    __declspec(dllexport)
    HRESULT InitDxgi(void* pSwapChain, HWND hwnd, const char* pipeName) {
        LOG_INFO("[DiscordSDK] InitDxgi called. pipe=%s", pipeName ? pipeName : "null");
        StartPipeKeepalive(pipeName);
        return S_OK;
    }

    // InitD3d12 — D3D12 swap chain varyantı
    // Gerçek imza: HRESULT InitD3d12(void* pSwapChain, HWND, const char* pipeName)
    __declspec(dllexport)
    HRESULT InitD3d12(void* pSwapChain, HWND hwnd, const char* pipeName) {
        LOG_INFO("[DiscordSDK] InitD3d12 called. pipe=%s", pipeName ? pipeName : "null");
        StartPipeKeepalive(pipeName);
        return S_OK;
    }

    // OnPresent — her frame'de DiscordHook64 tarafından çağrılır
    __declspec(dllexport)
    HRESULT OnPresent(void* pSwapChain, UINT syncInterval, UINT flags) {
        return S_OK;
    }

    // Klavye / fare event'leri
    __declspec(dllexport)
    HRESULT CharEvent(UINT ch) {
        if (renderer::g_imgui_ready && ImGui::GetCurrentContext()) {
            ImGui::GetIO().AddInputCharacter(ch);
        }
        return S_OK;
    }

    __declspec(dllexport)
    HRESULT KeyEvent(UINT vk, BOOL down) {
        if ((vk == VK_INSERT || vk == VK_DELETE) && down) {
            overlay_menu::g_open = !overlay_menu::g_open;
        }
        if (renderer::g_imgui_ready && ImGui::GetCurrentContext()) {
            ImGuiIO& io = ImGui::GetIO();
            ImGuiKey imgui_key = ImGui_ImplWin32_KeyEventToImGuiKey(vk, 0);
            if (imgui_key != ImGuiKey_None) {
                io.AddKeyEvent(imgui_key, down != 0);
            }
        }
        return S_OK;
    }

    __declspec(dllexport)
    HRESULT MouseButtonEvent(UINT btn, BOOL down, INT x, INT y) {
        if (renderer::g_imgui_ready && ImGui::GetCurrentContext()) {
            ImGuiIO& io = ImGui::GetIO();
            io.AddMousePosEvent((float)x, (float)y);
            int b = (btn == 0 ? 0 : (btn == 1 ? 1 : 2));
            io.AddMouseButtonEvent(b, down != 0);
        }
        return S_OK;
    }

    __declspec(dllexport)
    HRESULT MouseMotionEvent(INT x, INT y) {
        if (renderer::g_imgui_ready && ImGui::GetCurrentContext()) {
            ImGuiIO& io = ImGui::GetIO();
            io.AddMousePosEvent((float)x, (float)y);
        }
        return S_OK;
    }

    // IME
    __declspec(dllexport) HRESULT ImeCancelComposition()          { return S_OK; }
    __declspec(dllexport) HRESULT ImeCommitText(const wchar_t*)   { return S_OK; }
    __declspec(dllexport) HRESULT ImeSetComposition(const wchar_t*, void*, INT, INT) { return S_OK; }

    // Mesaj iletme
    __declspec(dllexport) HRESULT ForwardMessage(void* msg)       { return S_OK; }

    // Click zone — overlay'in click-through olup olmadığını bildirir
    __declspec(dllexport)
    BOOL PointInsideClickZone(INT x, INT y) {
        return overlay_menu::g_open ? TRUE : FALSE;
    }

    // IME callback setter'ları
    __declspec(dllexport) HRESULT SetImeCompositionRangeCallback(void* cb) { return S_OK; }
    __declspec(dllexport) HRESULT SetImeSelectionBoundsCallback(void* cb)  { return S_OK; }
}
// ─────────────────────────────────────────────────────────────────────────────

static HANDLE g_overlay_thread = nullptr;

// Process-local ESP verisi — UDP'den doldurulur
static SharedESPData g_local_esp = {};

static DWORD WINAPI overlay_main(LPVOID) {
    LOG_STEP("[overlay_main] Baslatildi.");
    if (!g_esp_data) {
        g_esp_data = &g_local_esp;
        ZeroMemory(g_esp_data, sizeof(SharedESPData));
    }
    g_esp_data->overlay_connected = true;

    LOG_STEP("[overlay_main] renderer::hook_present() cagriliyor...");
    renderer::hook_present();

    LOG_STEP("[overlay_main] renderer::render_loop() cagriliyor...");
    renderer::render_loop();

    LOG_STEP("[overlay_main] Temizleniyor...");
    renderer::unhook_present();
    return 0;
}

LONG WINAPI OverlayCrashHandler(PEXCEPTION_POINTERS pExceptionInfo) {
    if (!pExceptionInfo || !pExceptionInfo->ExceptionRecord)
        return EXCEPTION_CONTINUE_SEARCH;

    DWORD code = pExceptionInfo->ExceptionRecord->ExceptionCode;
    // Debugger/step/thread adı exception'larını geç
    if (code == EXCEPTION_BREAKPOINT  ||
        code == EXCEPTION_SINGLE_STEP ||
        code == 0x40010006            ||
        code == 0x406D1388) {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    Logger::LogCrash(pExceptionInfo, "overlay_entry::OverlayCrashHandler");
    return EXCEPTION_CONTINUE_SEARCH;
}

#if 0
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        AddVectoredExceptionHandler(1, OverlayCrashHandler);
        DisableThreadLibraryCalls(hModule);
        renderer::g_module = hModule;
        g_overlay_thread = CreateThread(nullptr, 0, overlay_main, nullptr, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH) {
        s_pipe_running = false;
        renderer::g_running = false;
        if (g_overlay_thread) {
            WaitForSingleObject(g_overlay_thread, 3000);
            CloseHandle(g_overlay_thread);
        }
    }
    return TRUE;
}
#endif
