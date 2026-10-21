#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <atomic>

namespace renderer {

    extern HMODULE              g_module;
    extern std::atomic<bool>    g_running;

    // D3D11 kaynak referansları
    extern ID3D11Device*            g_device;
    extern ID3D11DeviceContext*     g_context;
    extern ID3D11RenderTargetView*  g_rtv;

    // ImGui başlatma bayrağı
    extern bool g_imgui_ready;

    // WndProc
    extern HWND    g_hwnd;
    extern WNDPROC g_original_wndproc;

    typedef void (*RenderCallbackFn)();
    extern RenderCallbackFn g_render_callback;

    void hook_present();
    void render_loop();
    void unhook_present();

} // namespace renderer
