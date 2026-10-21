// overlay_render.cpp — D3D11 Present kancası + ImGui render döngüsü

#include "overlay_render.hpp"
#include "overlay_menu.hpp"
#include "Menu.h"
#include "jfmenu/headers/fonts.h"
#include "../shared.hpp"
#include "../logger.hpp"
#include "../Protection/call_spoof.h"
#include <iostream>
#include <dwmapi.h>
#include <timeapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "winmm.lib")

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <d3d11.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// ────────────────────────────────────────────────────────────────────────────
// Forward declaration (imgui_impl_win32.cpp tarafından sağlanır)
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace renderer {

    HMODULE               g_module       = nullptr;
    std::atomic<bool>     g_running      = true;
    ID3D11Device*         g_device       = nullptr;
    ID3D11DeviceContext*  g_context      = nullptr;
    ID3D11RenderTargetView* g_rtv        = nullptr;
    bool                  g_imgui_ready  = false;
    HWND                  g_hwnd         = nullptr;
    WNDPROC               g_original_wndproc = nullptr;
    RenderCallbackFn      g_render_callback  = nullptr;

    // ── typedef + orijinal Present pointer ───────────────────────────────────
    typedef HRESULT(STDMETHODCALLTYPE* Present_t)(IDXGISwapChain*, UINT, UINT);
    typedef HRESULT(STDMETHODCALLTYPE* ResizeBuffers_t)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    static Present_t        oPresent       = nullptr;
    static ResizeBuffers_t  oResizeBuffers = nullptr;
    static void**           g_vmt_present  = nullptr;
    static void**           g_vmt_resize   = nullptr;

    // ── WndProc hook ─────────────────────────────────────────────────────────
    static LRESULT CALLBACK hk_wndproc(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
        // INSERT tuşu → menü aç/kapat
        if (msg == WM_KEYDOWN && w == VK_INSERT) {
            overlay_menu::g_open = !overlay_menu::g_open;
            return 0;
        }

        // Menü açıksa ImGui'ye gönder
        if (overlay_menu::g_open) {
            ImGui_ImplWin32_WndProcHandler(hwnd, msg, w, l);
            // Fare ve klavye mesajlarını oyuna geçirme (menü açıkken)
            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP ||
                msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP ||
                msg == WM_MOUSEMOVE   || msg == WM_MOUSEWHEEL ||
                msg == WM_KEYDOWN     || msg == WM_KEYUP) {
                return 0;
            }
        }
        return CallWindowProcA(g_original_wndproc, hwnd, msg, w, l);
    }

    // ── ImGui renk teması (Stellarix dark) ───────────────────────────────────
    static void setup_imgui_style() {
        ImGuiStyle& s = ImGui::GetStyle();
        s.WindowRounding    = 6.0f;
        s.FrameRounding     = 4.0f;
        s.PopupRounding     = 4.0f;
        s.ScrollbarRounding = 4.0f;
        s.GrabRounding      = 4.0f;
        s.WindowBorderSize  = 1.0f;
        s.FrameBorderSize   = 0.0f;

        ImVec4* c = s.Colors;
        c[ImGuiCol_WindowBg]         = ImVec4(0.054f, 0.063f, 0.082f, 0.97f); // #0E1015
        c[ImGuiCol_TitleBg]          = ImVec4(0.075f, 0.086f, 0.122f, 1.0f);
        c[ImGuiCol_TitleBgActive]    = ImVec4(0.075f, 0.086f, 0.122f, 1.0f);
        c[ImGuiCol_Header]           = ImVec4(0.518f, 0.522f, 1.0f, 0.25f);  // indigo accent
        c[ImGuiCol_HeaderHovered]    = ImVec4(0.518f, 0.522f, 1.0f, 0.40f);
        c[ImGuiCol_HeaderActive]     = ImVec4(0.518f, 0.522f, 1.0f, 0.65f);
        c[ImGuiCol_Button]           = ImVec4(0.12f, 0.14f, 0.20f, 1.0f);
        c[ImGuiCol_ButtonHovered]    = ImVec4(0.518f, 0.522f, 1.0f, 0.30f);
        c[ImGuiCol_ButtonActive]     = ImVec4(0.518f, 0.522f, 1.0f, 0.55f);
        c[ImGuiCol_CheckMark]        = ImVec4(0.518f, 0.522f, 1.0f, 1.0f);
        c[ImGuiCol_SliderGrab]       = ImVec4(0.518f, 0.522f, 1.0f, 0.85f);
        c[ImGuiCol_SliderGrabActive] = ImVec4(0.518f, 0.522f, 1.0f, 1.0f);
        c[ImGuiCol_FrameBg]          = ImVec4(0.10f, 0.12f, 0.18f, 1.0f);
        c[ImGuiCol_FrameBgHovered]   = ImVec4(0.14f, 0.16f, 0.24f, 1.0f);
        c[ImGuiCol_FrameBgActive]    = ImVec4(0.18f, 0.20f, 0.30f, 1.0f);
        c[ImGuiCol_Separator]        = ImVec4(0.25f, 0.28f, 0.38f, 1.0f);
        c[ImGuiCol_Text]             = ImVec4(0.90f, 0.90f, 0.95f, 1.0f);
        c[ImGuiCol_TextDisabled]     = ImVec4(0.50f, 0.50f, 0.55f, 1.0f);
        c[ImGuiCol_Border]           = ImVec4(0.20f, 0.22f, 0.32f, 1.0f);
    }

    // ── ESP çizim fonksiyonları ───────────────────────────────────────────────
    static void draw_esp(ImDrawList* dl) {
        if (!g_esp_data || !g_esp_data->overlay_connected) return;
        if (g_render_callback) return; // Dahili oyun render callback'i (render_players) aktifse çizimi o yönetir

        const SharedSettings& cfg = g_esp_data->settings;
        int   cnt = g_esp_data->player_count;
        float sw  = g_esp_data->screen_w > 0.0f ? g_esp_data->screen_w : ImGui::GetIO().DisplaySize.x;
        float sh  = g_esp_data->screen_h > 0.0f ? g_esp_data->screen_h : ImGui::GetIO().DisplaySize.y;

        // Aimbot FOV Çemberi
        if (cfg.draw_f0v && cfg.a1m_f0v > 0.0f) {
            dl->AddCircle(
                ImVec2(sw * 0.5f, sh * 0.5f),
                cfg.a1m_f0v,
                IM_COL32(255, 255, 255, 180),
                64,
                1.2f
            );
        }

        for (int i = 0; i < cnt && i < MAX_PLAYERS; ++i) {
            const PlayerESP& p = g_esp_data->players[i];
            if (!p.valid || !p.alive) continue;

            // Team check — takım arkadaşını atla
            if (cfg.t3am_check && p.is_teammate) continue;

            // Renk seç
            ImU32 col;
            if (!cfg.t3am_check && p.is_teammate) {
                // Takım arkadaşı görünüyor → takım rengi
                col = IM_COL32(
                    (int)(cfg.team_r * 255),
                    (int)(cfg.team_g * 255),
                    (int)(cfg.team_b * 255),
                    (int)(cfg.team_a * 220));
            } else {
                col = p.visible
                    ? IM_COL32((int)(cfg.vis_r * 255),   (int)(cfg.vis_g * 255),   (int)(cfg.vis_b * 255),   220)
                    : IM_COL32((int)(cfg.invis_r * 255), (int)(cfg.invis_g * 255), (int)(cfg.invis_b * 255), 200);
            }

            float thick = cfg.esp_thickness;


            // 2D Bounding Box
            if (cfg.box2d) {
                dl->AddRect(
                    ImVec2(p.box_left, p.box_top),
                    ImVec2(p.box_right, p.box_bottom),
                    col, 0.0f, 0, thick
                );
            }

            // Corner Box
            if (cfg.corner) {
                float bw = p.box_right  - p.box_left;
                float bh = p.box_bottom - p.box_top;
                float cw = bw / 5.0f;
                float ch = bh / 5.0f;
                float l  = p.box_left, r = p.box_right;
                float t  = p.box_top,  b = p.box_bottom;

                // Köşe L şekilleri
                dl->AddLine(ImVec2(l, t),      ImVec2(l + cw, t),      col, thick);
                dl->AddLine(ImVec2(l, t),      ImVec2(l, t + ch),      col, thick);
                dl->AddLine(ImVec2(r - cw, t), ImVec2(r, t),           col, thick);
                dl->AddLine(ImVec2(r, t),      ImVec2(r, t + ch),      col, thick);
                dl->AddLine(ImVec2(l, b - ch), ImVec2(l, b),           col, thick);
                dl->AddLine(ImVec2(l, b),      ImVec2(l + cw, b),      col, thick);
                dl->AddLine(ImVec2(r, b - ch), ImVec2(r, b),           col, thick);
                dl->AddLine(ImVec2(r, b),      ImVec2(r - cw, b),      col, thick);
            }

            // 3D Box
            if (cfg.box3d && p.box3d_valid) {
                auto edge3d = [&](int a, int b) {
                    dl->AddLine(
                        ImVec2(p.box3d[a].x, p.box3d[a].y),
                        ImVec2(p.box3d[b].x, p.box3d[b].y),
                        col, thick
                    );
                };
                // Alt yüzey (0-1-2-3)
                edge3d(0, 1); edge3d(1, 2); edge3d(2, 3); edge3d(3, 0);
                // Üst yüzey (4-5-6-7)
                edge3d(4, 5); edge3d(5, 6); edge3d(6, 7); edge3d(7, 4);
                // Dikey kenarlar (0-4, 1-5, 2-6, 3-7)
                edge3d(0, 4); edge3d(1, 5); edge3d(2, 6); edge3d(3, 7);
            }

            // Skeleton — 14 kemik çizgisi
            if (cfg.sk3let0n) {
                // Bağlantı sırası: draw_skeleton'dan (hip=0,neck=1,uArmL=2,handL=3,handL1=4,
                //  uArmR=5,handR=6,handR1=7,lThigh=8,lCalf=9,lFoot=10,rThigh=11,rCalf=12,rFoot=13)
                auto bone = [&](int a, int b) {
                    if (a < MAX_BONES && b < MAX_BONES &&
                        p.bones[a].valid && p.bones[b].valid) {
                        dl->AddLine(
                            ImVec2(p.bones[a].x, p.bones[a].y),
                            ImVec2(p.bones[b].x, p.bones[b].y),
                            col, 1.2f
                        );
                    }
                };
                bone(0, 1);  // hip → neck
                bone(1, 2);  // neck → upperArmL
                bone(1, 5);  // neck → upperArmR
                bone(2, 3);  // upperArmL → handL
                bone(3, 4);  // handL → handL1
                bone(5, 6);  // upperArmR → handR
                bone(6, 7);  // handR → handR1
                bone(0, 8);  // hip → leftThigh
                bone(8, 9);  // leftThigh → leftCalf
                bone(9,10);  // leftCalf → leftFoot
                bone(0,11);  // hip → rightThigh
                bone(11,12); // rightThigh → rightCalf
                bone(12,13); // rightCalf → rightFoot
            }

            // Health bar (box'ın soluna dikey çubuk)
            if (cfg.h3althbar && p.health > 0) {
                float bw   = p.box_right - p.box_left;
                float bh   = p.box_bottom - p.box_top;
                float barX = p.box_left - 6.0f;
                float barT = p.box_top;
                float barB = p.box_bottom;
                float fillY = barB - bh * (p.health / 100.0f);

                // Arka plan
                dl->AddRectFilled(ImVec2(barX - 2, barT), ImVec2(barX + 2, barB),
                    IM_COL32(40, 40, 40, 200));
                // Can dolgu (yeşil → sarı → kırmızı)
                ImU32 hcol = p.health >= 75
                    ? IM_COL32(50, 220, 80, 230)
                    : (p.health >= 44 ? IM_COL32(230, 200, 50, 230) : IM_COL32(220, 50, 50, 230));
                dl->AddRectFilled(ImVec2(barX - 2, fillY), ImVec2(barX + 2, barB), hcol);

                // Kalkan (mavi, üstüne)
                if (p.shield > 0) {
                    float shFillY = fillY - bh * (p.shield / 100.0f);
                    dl->AddRectFilled(ImVec2(barX - 2, shFillY), ImVec2(barX + 2, fillY),
                        IM_COL32(80, 160, 240, 200));
                }
            }

            // Snapline (ekran ortasından ayağa)
            if (cfg.snapline) {
                dl->AddLine(
                    ImVec2(sw / 2.0f, sh),
                    ImVec2(p.foot_x, p.foot_y),
                    col, 1.0f
                );
            }

            // Head box (kafa üstüne küçük kare)
            if (cfg.headb0x) {
                float hw = (p.box_right - p.box_left) / 6.0f;
                float hh = hw;
                dl->AddRect(
                    ImVec2(p.head_x - hw / 2, p.head_y - hh / 2),
                    ImVec2(p.head_x + hw / 2, p.head_y + hh / 2),
                    col, 0.0f, 0, 1.2f
                );
            }
        }
    }

    // ── Bağımsız Overlay Penceresi ve Render Döngüsü ───────────────────────────
    static HWND g_overlay_hwnd = nullptr;
    static ID3D11Device* g_pd3dDevice = nullptr;
    static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
    static IDXGISwapChain* g_pSwapChain = nullptr;
    static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

    void CleanupRenderTarget() {
        if (g_mainRenderTargetView) {
            g_mainRenderTargetView->Release();
            g_mainRenderTargetView = nullptr;
        }
    }

    void CreateRenderTarget() {
        CleanupRenderTarget();
        if (!g_pSwapChain || !g_pd3dDevice) return;
        ID3D11Texture2D* pBackBuffer = nullptr;
        HRESULT hr = g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        if (SUCCEEDED(hr) && pBackBuffer) {
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
            pBackBuffer->Release();
        }
    }

    bool CreateDeviceD3D(HWND hWnd) {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
        if (hr != S_OK) {
            LOG_ERROR("[overlay_render] D3D11CreateDeviceAndSwapChain BASARISIZ! HRESULT: 0x%08X", hr);
            return false;
        }

        LOG_INFO("[overlay_render] D3D11 Device & SwapChain basariyla olusturuldu.");
        CreateRenderTarget();
        return true;
    }

    void CleanupDeviceD3D() {
        CleanupRenderTarget();
        if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
        if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
        if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    }

    LRESULT WINAPI WndProcOverlay(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg) {
        case WM_NCHITTEST:
            // Menü kapalıysa tıklar doğrudan altındaki pencereye (oyuna) akar
            if (!overlay_menu::g_open)
                return HTTRANSPARENT;
            return HTCLIENT;

        case WM_MOUSEACTIVATE:
            if (overlay_menu::g_open)
                return MA_ACTIVATE;
            else
                return MA_NOACTIVATEANDEAT;

        case WM_SIZE:
            if (g_pd3dDevice != nullptr && g_pSwapChain != nullptr && wParam != SIZE_MINIMIZED) {
                UINT w = (UINT)LOWORD(lParam);
                UINT h = (UINT)HIWORD(lParam);
                if (w > 0 && h > 0) {
                    CleanupRenderTarget();
                    g_pSwapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
                    CreateRenderTarget();
                }
            }
            return 0;

        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) return 0;
            break;

        case WM_DESTROY:
            LOG_INFO("[overlay_render] WndProcOverlay WM_DESTROY alindi.");
            ::PostQuitMessage(0);
            return 0;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

    void hook_present() {
        LOG_STEP("[overlay_render] hook_present() baslatildi...");

        // ── 1. Pencere sınıfı — gerçek DiscordHook64'ün kaydettiği isim
        WNDCLASSEXW wc   = {};
        wc.cbSize        = sizeof(WNDCLASSEXW);
        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc   = WndProcOverlay;
        wc.hInstance     = GetModuleHandle(nullptr);
        wc.lpszClassName = L"DiscordOverlay";   // gerçek Discord sınıf adı

        ATOM atom = ::RegisterClassExW(&wc);
        if (!atom && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
            LOG_WARN("[overlay_render] RegisterClassExW basarisiz. GLE=%lu", GetLastError());
        }

        int screenW = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        int screenH = GetSystemMetrics(SM_CYVIRTUALSCREEN);
        int originX = GetSystemMetrics(SM_XVIRTUALSCREEN);
        int originY = GetSystemMetrics(SM_YVIRTUALSCREEN);
        LOG_INFO("[overlay_render] Ekran: %d x %d @ (%d,%d)", screenW, screenH, originX, originY);

        // ── 2. Pencere stili — gerçek Discord Overlay ile birebir
        //   Gerçek DiscordHook64: WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED
        //   WS_EX_TOOLWINDOW KULLANMA — taskbar'dan gizler ama antiyang da tespit eder
        DWORD exStyle = WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE;

        g_overlay_hwnd = ::CreateWindowExW(
            exStyle,
            L"DiscordOverlay",          // class
            L"Discord Overlay",         // title — gerçek Discord ile aynı
            WS_POPUP | WS_VISIBLE,
            originX, originY, screenW, screenH,
            nullptr, nullptr, wc.hInstance, nullptr
        );

        if (!g_overlay_hwnd) {
            LOG_ERROR("[overlay_render] CreateWindowExW BASARISIZ! GLE=%lu", GetLastError());
            return;
        }
        LOG_INFO("[overlay_render] Overlay HWND=0x%p", g_overlay_hwnd);

        // ── 3. Layered attributes — gerçek Discord: LWA_COLORKEY (siyah) + tam alfa
        SetLayeredWindowAttributes(g_overlay_hwnd, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);

        // ── 4. DWM — tüm frame'i client'a extend et (gerçek Discord gibi)
        MARGINS margins = { -1, -1, -1, -1 };
        DwmExtendFrameIntoClientArea(g_overlay_hwnd, &margins);

        // ── 5. Ekran yakalamada görünmesi için WDA_NONE (0) ayarlanır (videolarda ve kayıtlarda görünür)
        typedef BOOL(WINAPI* pfnSetWindowDisplayAffinity)(HWND, DWORD);
        if (auto fn = (pfnSetWindowDisplayAffinity)GetProcAddress(
                GetModuleHandleW(L"user32.dll"), "SetWindowDisplayAffinity")) {
            fn(g_overlay_hwnd, 0 /*WDA_NONE - videolarda ve kayıtlarda görünür*/);
        }

        // ── 6. D3D11 cihazını oluştur
        if (!CreateDeviceD3D(g_overlay_hwnd)) {
            LOG_ERROR("[overlay_render] CreateDeviceD3D basarisiz!");
            CleanupDeviceD3D();
            ::UnregisterClassW(L"DiscordOverlay", wc.hInstance);
            return;
        }

        // ── 7. Z-order garantisi — en üstte tut, HWND_TOPMOST
        ::SetWindowPos(g_overlay_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

        ::ShowWindow(g_overlay_hwnd, SW_SHOW);
        ::UpdateWindow(g_overlay_hwnd);

        // ── 8. ImGui başlat
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

        setup_imgui_style();
        ImGui_ImplWin32_Init(g_overlay_hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        font->init_defaults();
        font->update();

        g_imgui_ready = true;
        timeBeginPeriod(1);
        LOG_INFO("[overlay_render] ImGui hazir.");
    }


    static void RenderSingleFrame(const ImVec4& clear_color) {
        __try {
            if (!g_pd3dDeviceContext || !g_pSwapChain) return;

            if (!g_mainRenderTargetView) {
                CreateRenderTarget();
                if (!g_mainRenderTargetView) return;
            }

            font->update();
            Menu::Init(g_pd3dDevice, g_pd3dDeviceContext, g_pSwapChain, g_overlay_hwnd);

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::GetIO().MouseDrawCursor = overlay_menu::g_open;

            ImDrawList* dl = ImGui::GetBackgroundDrawList();
            draw_esp(dl);

            if (g_render_callback) {
                g_render_callback();
            }

            if (overlay_menu::g_open) {
                overlay_menu::render();
            }

            ImGui::Render();
            const float clear_color_with_alpha[4] = {
                clear_color.x * clear_color.w,
                clear_color.y * clear_color.w,
                clear_color.z * clear_color.w,
                clear_color.w
            };
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
            ImDrawData* drawData = ImGui::GetDrawData();
            if (drawData) {
                ImGui_ImplDX11_RenderDrawData(drawData);
            }

            HRESULT hrPresent = g_pSwapChain->Present(0, DXGI_PRESENT_DO_NOT_WAIT);
            if (hrPresent != S_OK && hrPresent != DXGI_STATUS_OCCLUDED && hrPresent != DXGI_ERROR_WAS_STILL_DRAWING) {
                LOG_ERROR("[overlay_render] Present basarisiz! HRESULT: 0x%08X", hrPresent);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            LOG_ERROR("[overlay_render] RenderSingleFrame icinde exception yakalandi! Kod: 0x%08X", GetExceptionCode());
        }
    }

    void render_loop() {
        LOG_STEP("[overlay_render] render_loop() dongusune girildi.");
        ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        
        static HWND s_last_game_hwnd = nullptr;

        while (msg.message != WM_QUIT && g_running) {
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT) {
                    g_running = false;
                    break;
                }
            }

            if (!g_imgui_ready) { Sleep(10); continue; }

            // Menü tuşu kontrolü (INSERT veya DELETE)
            static bool insert_pressed = false;
            if ((HIDE_ASM(GetAsyncKeyState)(VK_INSERT) & 0x8000) || (HIDE_ASM(GetAsyncKeyState)(VK_DELETE) & 0x8000)) {
                if (!insert_pressed) {
                    overlay_menu::g_open = !overlay_menu::g_open;
                    insert_pressed = true;
                    LOG_INFO("[overlay_render] INSERT/DELETE tusuna basildi! Yeni menu durumu: %s", overlay_menu::g_open ? "ACIK" : "KAPALI");
                }
            } else {
                insert_pressed = false;
            }

            // Menü açılma/kapanma durumunu takip et ve pencere stillerini/tıklanabilirliğini güncelle
            static bool last_menu_open = false;
            if (overlay_menu::g_open != last_menu_open) {
                last_menu_open = overlay_menu::g_open;
                long ex_style = GetWindowLong(g_overlay_hwnd, GWL_EXSTYLE);
                if (overlay_menu::g_open) {
                    // Mevcut foreground penceresini (oyun) sakla
                    HWND fg = ::GetForegroundWindow();
                    if (fg && fg != g_overlay_hwnd) {
                        s_last_game_hwnd = fg;
                    }

                    ex_style &= ~(WS_EX_TRANSPARENT | WS_EX_NOACTIVATE); // Tıklamaları ve odaklanmayı al
                    SetWindowLong(g_overlay_hwnd, GWL_EXSTYLE, ex_style);
                    SetWindowPos(g_overlay_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

                    // AttachThreadInput ile foreground lock bypass — 3-4 tık gecikmesi tamamen çözülür
                    HWND hForeWnd = ::GetForegroundWindow();
                    DWORD foreThread = hForeWnd ? ::GetWindowThreadProcessId(hForeWnd, nullptr) : 0;
                    DWORD currentThread = ::GetCurrentThreadId();
                    if (foreThread && foreThread != currentThread) {
                        ::AttachThreadInput(currentThread, foreThread, TRUE);
                        ::BringWindowToTop(g_overlay_hwnd);
                        ::SetForegroundWindow(g_overlay_hwnd);
                        ::SetActiveWindow(g_overlay_hwnd);
                        ::SetFocus(g_overlay_hwnd);
                        ::AttachThreadInput(currentThread, foreThread, FALSE);
                    } else {
                        ::BringWindowToTop(g_overlay_hwnd);
                        ::SetForegroundWindow(g_overlay_hwnd);
                        ::SetActiveWindow(g_overlay_hwnd);
                        ::SetFocus(g_overlay_hwnd);
                    }
                } else {
                    ex_style |= (WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);  // Tıklamaları oyuna geçir
                    SetWindowLong(g_overlay_hwnd, GWL_EXSTYLE, ex_style);
                    SetWindowPos(g_overlay_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);

                    // Oyuna odağı hemen geri ver — fare takılması ve oyun kontrol kaybı çözülür
                    if (s_last_game_hwnd && ::IsWindow(s_last_game_hwnd)) {
                        ::SetForegroundWindow(s_last_game_hwnd);
                        ::SetActiveWindow(s_last_game_hwnd);
                    }
                }
            }

            // Menü açıkken fare konumunu ve tıklamaları doğrudan ImGui IO'ya aktar (ilk tıkta anında tepki)
            if (overlay_menu::g_open) {
                POINT pt;
                if (::GetCursorPos(&pt) && ::ScreenToClient(g_overlay_hwnd, &pt)) {
                    ImGui::GetIO().AddMousePosEvent((float)pt.x, (float)pt.y);
                }
                bool lmb = (HIDE_ASM(GetAsyncKeyState)(VK_LBUTTON) & 0x8000) != 0;
                ImGui::GetIO().AddMouseButtonEvent(0, lmb);
                bool rmb = (HIDE_ASM(GetAsyncKeyState)(VK_RBUTTON) & 0x8000) != 0;
                ImGui::GetIO().AddMouseButtonEvent(1, rmb);
            }

            RenderSingleFrame(clear_color);

            Sleep(4); // ~250 FPS tavan — CPU spike olmaz, oyun etkilenmez
        }
        LOG_STEP("[overlay_render] render_loop() tamamlandi.");
    }

    void unhook_present() {
        LOG_STEP("[overlay_render] unhook_present() cagrildi, kaynaklar serbest birakiliyor.");
        if (g_imgui_ready) {
            timeEndPeriod(1);
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
            g_imgui_ready = false;
        }
        CleanupDeviceD3D();
        if (g_overlay_hwnd) {
            ::DestroyWindow(g_overlay_hwnd);
            ::UnregisterClassW(L"DiscordOverlay", GetModuleHandle(nullptr));
            g_overlay_hwnd = nullptr;
        }
    }

} // namespace renderer
