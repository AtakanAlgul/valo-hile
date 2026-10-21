#define IMGUI_DEFINE_MATH_OPERATORS
#include "overlay_menu.hpp"
#include "Menu.h"
#include "jfmenu/headers/includes.h"
#include "../shared.hpp"
#include "ipc_client.hpp"
#include <Windows.h>
#include <ShlObj.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

namespace overlay_menu {
    bool g_open = true;
}

namespace {
    std::string CfgPath() {
        char doc[MAX_PATH] = {};
        if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_PERSONAL, nullptr, 0, doc)))
            return std::string(doc) + "\\V-core.cfg";
        return "V-core.cfg";
    }
    void WriteCol(std::ofstream& f, const char* n, const float* c) {
        f << n << "=" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << "\n";
    }
    bool ReadCol(const std::string& v, float* c) {
        return sscanf_s(v.c_str(), "%f,%f,%f,%f", &c[0], &c[1], &c[2], &c[3]) == 4;
    }
    std::string ExeDir() {
        char p[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, p, MAX_PATH);
        std::string s(p);
        size_t f = s.find_last_of("\\/");
        return (f == std::string::npos) ? "" : s.substr(0, f + 1);
    }
}

void Menu::SaveConfig() {
    std::ofstream f(CfgPath(), std::ios::trunc);
    if (!f.is_open()) return;
    f << "Aimbot=" << (Settings::Aimbot ? 1 : 0) << "\n";
    f << "AimVisCheck=" << (Settings::AimVisCheck ? 1 : 0) << "\n";
    f << "RecoilControl=" << (Settings::RecoilControl ? 1 : 0) << "\n";
    f << "DrawFov=" << (Settings::DrawFov ? 1 : 0) << "\n";
    f << "FilledFov=" << (Settings::FilledFov ? 1 : 0) << "\n";
    f << "AimSmooth=" << Settings::AimSmooth << "\n";
    f << "AimFov=" << Settings::AimFov << "\n";
    f << "AimBone=" << Settings::AimBone << "\n";
    f << "AimKey=" << Settings::AimKey << "\n";
    f << "Triggerbot=" << (Settings::Triggerbot ? 1 : 0) << "\n";
    f << "TriggerDelay=" << Settings::TriggerDelay << "\n";
    f << "RcsStrength=" << Settings::RcsStrength << "\n";
    f << "BoxEsp=" << (Settings::BoxEsp ? 1 : 0) << "\n";
    f << "CornerBox=" << (Settings::CornerBox ? 1 : 0) << "\n";
    f << "Box3D=" << (Settings::Box3D ? 1 : 0) << "\n";
    f << "Skeleton=" << (Settings::Skeleton ? 1 : 0) << "\n";
    f << "VisibleCheck=" << (Settings::VisibilityCheck ? 1 : 0) << "\n";
    f << "TeamCheck=" << (Settings::TeamCheck ? 1 : 0) << "\n";
    f << "IgnoreDormant=" << (Settings::IgnoreDormant ? 1 : 0) << "\n";
    f << "Snaplines=" << (Settings::Snaplines ? 1 : 0) << "\n";
    f << "Distance=" << (Settings::Distance ? 1 : 0) << "\n";
    f << "HealthBar=" << (Settings::HealthBar ? 1 : 0) << "\n";
    f << "HeadBox=" << (Settings::HeadBox ? 1 : 0) << "\n";
    f << "BodyDot=" << (Settings::BodyDot ? 1 : 0) << "\n";
    f << "MemoryRadar=" << (Settings::MemoryRadar ? 1 : 0) << "\n";
    f << "SpikeTimer=" << (Settings::SpikeTimer ? 1 : 0) << "\n";
    f << "ViewAngle=" << (Settings::ViewAngle ? 1 : 0) << "\n";
    f << "AgentIcons=" << (Settings::AgentIcons ? 1 : 0) << "\n";
    f << "RainbowSkeleton=" << (Settings::RainbowSkeleton ? 1 : 0) << "\n";
    f << "EspThickness=" << Settings::EspThickness << "\n";
    f << "LegitEsp=" << (Settings::LegitEsp ? 1 : 0) << "\n";
    f << "Watermark=" << (Settings::Watermark ? 1 : 0) << "\n";
    f << "LegitKey=" << Settings::LegitKey << "\n";
    f << "LegitMode=" << Settings::LegitMode << "\n";
    f << "LegitTime=" << Settings::LegitTime << "\n";
    WriteCol(f, "BoxColor", Settings::BoxColor);
    WriteCol(f, "SnaplineColor", Settings::SnaplineColor);
    WriteCol(f, "HeadBoxColor", Settings::HeadBoxColor);
    WriteCol(f, "BodyDotColor", Settings::BodyDotColor);
    WriteCol(f, "DistanceColor", Settings::DistanceColor);
    WriteCol(f, "HPHighColor", Settings::HPHighColor);
    WriteCol(f, "HPLowColor", Settings::HPLowColor);
    WriteCol(f, "TeamColor", Settings::TeamColor);
}

void Menu::LoadConfig() {
    std::ifstream f(CfgPath());
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        size_t e = line.find('=');
        if (e == std::string::npos) continue;
        std::string n = line.substr(0, e), v = line.substr(e + 1);
        int iv = atoi(v.c_str());
        float fv = (float)atof(v.c_str());
        bool b = iv != 0;
        if (n == "Aimbot") Settings::Aimbot = b;
        else if (n == "AimVisCheck") Settings::AimVisCheck = b;
        else if (n == "RecoilControl") Settings::RecoilControl = b;
        else if (n == "DrawFov") Settings::DrawFov = b;
        else if (n == "FilledFov") Settings::FilledFov = b;
        else if (n == "AimSmooth") Settings::AimSmooth = fv;
        else if (n == "AimFov") Settings::AimFov = fv;
        else if (n == "AimBone") Settings::AimBone = iv;
        else if (n == "AimKey") Settings::AimKey = iv;
        else if (n == "Triggerbot") Settings::Triggerbot = b;
        else if (n == "TriggerDelay") Settings::TriggerDelay = iv;
        else if (n == "RcsStrength") Settings::RcsStrength = fv;
        else if (n == "BoxEsp") Settings::BoxEsp = b;
        else if (n == "CornerBox") Settings::CornerBox = b;
        else if (n == "Box3D") Settings::Box3D = b;
        else if (n == "Skeleton") Settings::Skeleton = b;
        else if (n == "VisibleCheck") Settings::VisibilityCheck = b;
        else if (n == "TeamCheck") Settings::TeamCheck = b;
        else if (n == "IgnoreDormant") Settings::IgnoreDormant = b;
        else if (n == "Snaplines") Settings::Snaplines = b;
        else if (n == "Distance") Settings::Distance = b;
        else if (n == "HealthBar") Settings::HealthBar = b;
        else if (n == "HeadBox") Settings::HeadBox = b;
        else if (n == "BodyDot") Settings::BodyDot = b;
        else if (n == "MemoryRadar") Settings::MemoryRadar = b;
        else if (n == "SpikeTimer") Settings::SpikeTimer = b;
        else if (n == "ViewAngle") Settings::ViewAngle = b;
        else if (n == "AgentIcons") Settings::AgentIcons = b;
        else if (n == "RainbowSkeleton") Settings::RainbowSkeleton = b;
        else if (n == "EspThickness") Settings::EspThickness = fv;
        else if (n == "LegitEsp") Settings::LegitEsp = b;
        else if (n == "Watermark") Settings::Watermark = b;
        else if (n == "LegitKey") Settings::LegitKey = iv;
        else if (n == "LegitMode") Settings::LegitMode = iv;
        else if (n == "LegitTime") { if (iv >= 1 && iv <= 50) Settings::LegitTime = iv; }
        else if (n == "BoxColor") ReadCol(v, Settings::BoxColor);
        else if (n == "SnaplineColor") ReadCol(v, Settings::SnaplineColor);
        else if (n == "HeadBoxColor") ReadCol(v, Settings::HeadBoxColor);
        else if (n == "BodyDotColor") ReadCol(v, Settings::BodyDotColor);
        else if (n == "DistanceColor") ReadCol(v, Settings::DistanceColor);
        else if (n == "HPHighColor") ReadCol(v, Settings::HPHighColor);
        else if (n == "HPLowColor") ReadCol(v, Settings::HPLowColor);
        else if (n == "TeamColor") ReadCol(v, Settings::TeamColor);
    }
    SyncToCfg();
}

void Menu::ResetConfig() {
    Settings::Aimbot = true;
    Settings::AimVisCheck = true;
    Settings::RecoilControl = true;
    Settings::DrawFov = true;
    Settings::FilledFov = false;
    Settings::AimSmooth = 10.0f;
    Settings::AimFov = 40.0f;
    Settings::AimBone = 0;
    Settings::AimKey = 0x01;
    Settings::Triggerbot = false;
    Settings::TriggerDelay = 90;
    Settings::RcsStrength = 0.6f;
    Settings::BoxEsp = true;
    Settings::CornerBox = true;
    Settings::Box3D = false;
    Settings::Skeleton = true;
    Settings::VisibilityCheck = false;
    Settings::TeamCheck = true;
    Settings::IgnoreDormant = true;
    Settings::Snaplines = false;
    Settings::Distance = true;
    Settings::HealthBar = true;
    Settings::HeadBox = false;
    Settings::BodyDot = false;
    Settings::MemoryRadar = false;
    Settings::SpikeTimer = false;
    Settings::ViewAngle = false;
    Settings::AgentIcons = false;
    Settings::RainbowSkeleton = false;
    Settings::EspThickness = 1.0f;
    Settings::LegitEsp = false;
    Settings::Watermark = false;
    Settings::LegitKey = 0x06;
    Settings::LegitMode = 0;
    Settings::LegitTime = 10;
    const float red[4] = { 0.941f, 0.173f, 0.337f, 1.f };
    const float wht[4] = { 1.f, 1.f, 1.f, 1.f };
    const float grn[4] = { 0.f, 1.f, 0.f, 1.f };
    const float red2[4] = { 1.f, 0.f, 0.f, 1.f };
    memcpy(Settings::BoxColor, wht, sizeof(wht));
    memcpy(Settings::SnaplineColor, red, sizeof(red));
    memcpy(Settings::HeadBoxColor, red, sizeof(red));
    memcpy(Settings::BodyDotColor, red, sizeof(red));
    memcpy(Settings::DistanceColor, red, sizeof(red));
    memcpy(Settings::HPHighColor, grn, sizeof(grn));
    memcpy(Settings::HPLowColor, red2, sizeof(red2));
    memcpy(Settings::TeamColor, grn, sizeof(grn));
    DeleteFileA(CfgPath().c_str());
    SyncToCfg();
}

static int ImGuiKeyToVK(int k) {
    switch (k) {
    case ImGuiKey_MouseLeft: return VK_LBUTTON;
    case ImGuiKey_MouseRight: return VK_RBUTTON;
    case ImGuiKey_MouseMiddle: return VK_MBUTTON;
    case ImGuiKey_MouseX1: return VK_XBUTTON1;
    case ImGuiKey_MouseX2: return VK_XBUTTON2;
    case ImGuiKey_Space: return VK_SPACE;
    case ImGuiKey_Escape: return VK_ESCAPE;
    case ImGuiKey_Tab: return VK_TAB;
    case ImGuiKey_Insert: return VK_INSERT;
    case ImGuiKey_Delete: return VK_DELETE;
    case ImGuiKey_Home: return VK_HOME;
    case ImGuiKey_End: return VK_END;
    case ImGuiKey_PageUp: return VK_PRIOR;
    case ImGuiKey_PageDown: return VK_NEXT;
    case ImGuiKey_LeftArrow: return VK_LEFT;
    case ImGuiKey_RightArrow: return VK_RIGHT;
    case ImGuiKey_UpArrow: return VK_UP;
    case ImGuiKey_DownArrow: return VK_DOWN;
    case ImGuiKey_LeftShift: case ImGuiKey_RightShift: return VK_SHIFT;
    case ImGuiKey_LeftCtrl: case ImGuiKey_RightCtrl: return VK_CONTROL;
    case ImGuiKey_LeftAlt: case ImGuiKey_RightAlt: return VK_MENU;
    case ImGuiKey_0: return '0'; case ImGuiKey_1: return '1'; case ImGuiKey_2: return '2';
    case ImGuiKey_3: return '3'; case ImGuiKey_4: return '4'; case ImGuiKey_5: return '5';
    case ImGuiKey_6: return '6'; case ImGuiKey_7: return '7'; case ImGuiKey_8: return '8';
    case ImGuiKey_9: return '9';
    case ImGuiKey_A: return 'A'; case ImGuiKey_B: return 'B'; case ImGuiKey_C: return 'C';
    case ImGuiKey_D: return 'D'; case ImGuiKey_E: return 'E'; case ImGuiKey_F: return 'F';
    case ImGuiKey_G: return 'G'; case ImGuiKey_H: return 'H'; case ImGuiKey_I: return 'I';
    case ImGuiKey_J: return 'J'; case ImGuiKey_K: return 'K'; case ImGuiKey_L: return 'L';
    case ImGuiKey_M: return 'M'; case ImGuiKey_N: return 'N'; case ImGuiKey_O: return 'O';
    case ImGuiKey_P: return 'P'; case ImGuiKey_R: return 'R'; case ImGuiKey_S: return 'S';
    case ImGuiKey_T: return 'T'; case ImGuiKey_U: return 'U'; case ImGuiKey_V: return 'V';
    case ImGuiKey_W: return 'W'; case ImGuiKey_X: return 'X'; case ImGuiKey_Y: return 'Y';
    case ImGuiKey_Z: return 'Z';
    case ImGuiKey_F1: return VK_F1; case ImGuiKey_F2: return VK_F2; case ImGuiKey_F3: return VK_F3;
    case ImGuiKey_F4: return VK_F4; case ImGuiKey_F5: return VK_F5; case ImGuiKey_F6: return VK_F6;
    case ImGuiKey_F7: return VK_F7; case ImGuiKey_F8: return VK_F8; case ImGuiKey_F9: return VK_F9;
    case ImGuiKey_F10: return VK_F10; case ImGuiKey_F11: return VK_F11; case ImGuiKey_F12: return VK_F12;
    default: break;
    }
    return -1;
}

static int VKToImGuiKey(int vk) {
    switch (vk) {
    case VK_LBUTTON: return ImGuiKey_MouseLeft;
    case VK_RBUTTON: return ImGuiKey_MouseRight;
    case VK_MBUTTON: return ImGuiKey_MouseMiddle;
    case VK_XBUTTON1: return ImGuiKey_MouseX1;
    case VK_XBUTTON2: return ImGuiKey_MouseX2;
    case VK_SPACE: return ImGuiKey_Space;
    case VK_ESCAPE: return ImGuiKey_Escape;
    case VK_TAB: return ImGuiKey_Tab;
    case VK_INSERT: return ImGuiKey_Insert;
    case VK_DELETE: return ImGuiKey_Delete;
    case VK_HOME: return ImGuiKey_Home;
    case VK_END: return ImGuiKey_End;
    case VK_PRIOR: return ImGuiKey_PageUp;
    case VK_NEXT: return ImGuiKey_PageDown;
    case VK_LEFT: return ImGuiKey_LeftArrow;
    case VK_RIGHT: return ImGuiKey_RightArrow;
    case VK_UP: return ImGuiKey_UpArrow;
    case VK_DOWN: return ImGuiKey_DownArrow;
    case VK_SHIFT: return ImGuiKey_LeftShift;
    case VK_CONTROL: return ImGuiKey_LeftCtrl;
    case VK_MENU: return ImGuiKey_LeftAlt;
    default: break;
    }
    if (vk >= '0' && vk <= '9') return ImGuiKey_0 + (vk - '0');
    if (vk >= 'A' && vk <= 'Z') return ImGuiKey_A + (vk - 'A');
    if (vk >= 'a' && vk <= 'z') return ImGuiKey_A + (vk - 'a');
    if (vk >= VK_F1 && vk <= VK_F12) return ImGuiKey_F1 + (vk - VK_F1);
    return ImGuiKey_None;
}

void Menu::SyncFromCfg() {
    Settings::Aimbot = cfg->get<checkbox_t>("Enable Aimbot").enabled;
    Settings::DrawFov = cfg->get<checkbox_t>("Draw FOV").enabled;
    Settings::FilledFov = cfg->get<checkbox_t>("Filled FOV").enabled;
    Settings::AimVisCheck = cfg->get<checkbox_t>("Visibility Check").enabled;
    Settings::RecoilControl = cfg->get<checkbox_t>("Recoil Control").enabled;
    Settings::RcsStrength = cfg->get<slider_t>("RCS Strength").callback;
    Settings::Triggerbot = cfg->get<checkbox_t>("Triggerbot").enabled;
    Settings::TriggerDelay = (int)cfg->get<slider_t>("Trigger Delay").callback;
    Settings::AimBone = cfg->get<dropdown_t>("Target Bone").callback;
    Settings::AimFov = cfg->get<slider_t>("FOV").callback;
    Settings::AimSmooth = cfg->get<slider_t>("Smooth").callback;

    auto& aimBinds = cfg->get<checkbox_t>("Enable Aimbot").keybinds_list;
    if (!aimBinds.empty()) {
        int vk = ImGuiKeyToVK(aimBinds[0].key);
        if (vk > 0) Settings::AimKey = vk;
    }

    Settings::BoxEsp = cfg->get<checkbox_t>("Box ESP").enabled;
    Settings::CornerBox = cfg->get<checkbox_t>("Corner Box").enabled;
    Settings::Box3D = cfg->get<checkbox_t>("3D Box").enabled;
    Settings::Skeleton = cfg->get<checkbox_t>("Skeleton").enabled;
    Settings::HeadBox = cfg->get<checkbox_t>("Head Box").enabled;
    Settings::BodyDot = cfg->get<checkbox_t>("Body Dot").enabled;
    Settings::HealthBar = cfg->get<checkbox_t>("Health Bar").enabled;
    Settings::Snaplines = cfg->get<checkbox_t>("Snaplines").enabled;
    Settings::Distance = cfg->get<checkbox_t>("Distance").enabled;
    Settings::TeamCheck = cfg->get<checkbox_t>("Team Check").enabled;
    Settings::VisibilityCheck = cfg->get<checkbox_t>("Visible Check").enabled;
    Settings::IgnoreDormant = cfg->get<checkbox_t>("Ignore Dormant").enabled;
    Settings::MemoryRadar = cfg->get<checkbox_t>("Memory Radar").enabled;
    Settings::SpikeTimer = cfg->get<checkbox_t>("Spike Timer").enabled;
    Settings::ViewAngle = cfg->get<checkbox_t>("View Angle").enabled;
    Settings::AgentIcons = cfg->get<checkbox_t>("Agent Icons").enabled;
    Settings::RainbowSkeleton = cfg->get<checkbox_t>("Rainbow Skeleton").enabled;
    Settings::EspThickness = cfg->get<slider_t>("ESP Thickness").callback;
    Settings::LegitEsp = cfg->get<checkbox_t>("Legit ESP").enabled;
    Settings::Watermark = cfg->get<checkbox_t>("Watermark").enabled;
    Settings::LegitMode = cfg->get<dropdown_t>("Legit Mode").callback;
    Settings::LegitTime = (int)cfg->get<slider_t>("Legit Time").callback;
    if (Settings::LegitTime < 1) Settings::LegitTime = 1;
    if (Settings::LegitTime > 50) Settings::LegitTime = 50;
    auto& binds = cfg->get<checkbox_t>("Legit ESP").keybinds_list;
    if (!binds.empty()) {
        int vk = ImGuiKeyToVK(binds[0].key);
        if (vk > 0) Settings::LegitKey = vk;
    }

    // SharedESPData'ya doğrudan aktar
    if (g_esp_data) {
        auto& s = g_esp_data->settings;
        s.a1mbot = Settings::Aimbot;
        s.a1m_v1sh_ch3ck = Settings::AimVisCheck;
        s.reco1l_contr0l = Settings::RecoilControl;
        s.draw_f0v = Settings::DrawFov;
        s.filled_f0v = Settings::FilledFov;
        s.a1m_sm00th = Settings::AimSmooth;
        s.a1m_f0v = Settings::AimFov;
        s.a1m_b0ne = Settings::AimBone;
        s.a1m_k3y = Settings::AimKey;
        s.tr1ggerbot = Settings::Triggerbot;
        s.fl1ck_delay = Settings::TriggerDelay;
        s.rcs_strength = Settings::RcsStrength;

        s.box2d = Settings::BoxEsp;
        s.corner = Settings::CornerBox;
        s.box3d = Settings::Box3D;
        s.sk3let0n = Settings::Skeleton;
        s.h3althbar = Settings::HealthBar;
        s.headb0x = Settings::HeadBox;
        s.snapline = Settings::Snaplines;
        s.vischeck = Settings::VisibilityCheck;
        s.esp_thickness = Settings::EspThickness;
        s.t3am_check = Settings::TeamCheck;
        s.player_dist = Settings::Distance;
        s.dormant = Settings::IgnoreDormant;
        s.spiketimer = Settings::SpikeTimer;
        s.radar = Settings::MemoryRadar;
        s.view_angle = Settings::ViewAngle;
        s.agent_icons = Settings::AgentIcons;
        s.rainbow_skel = Settings::RainbowSkeleton;

        // Renkler
        s.vis_r = Settings::BoxColor[0];
        s.vis_g = Settings::BoxColor[1];
        s.vis_b = Settings::BoxColor[2];
        s.vis_a = Settings::BoxColor[3];

        s.invis_r = Settings::SnaplineColor[0];
        s.invis_g = Settings::SnaplineColor[1];
        s.invis_b = Settings::SnaplineColor[2];
        s.invis_a = Settings::SnaplineColor[3];

        s.team_r = Settings::TeamColor[0];
        s.team_g = Settings::TeamColor[1];
        s.team_b = Settings::TeamColor[2];
        s.team_a = Settings::TeamColor[3];
    }
}

void Menu::SyncToCfg() {
    cfg->get<checkbox_t>("Enable Aimbot").enabled = Settings::Aimbot;
    cfg->get<checkbox_t>("Draw FOV").enabled = Settings::DrawFov;
    cfg->get<checkbox_t>("Filled FOV").enabled = Settings::FilledFov;
    cfg->get<checkbox_t>("Visibility Check").enabled = Settings::AimVisCheck;
    cfg->get<checkbox_t>("Recoil Control").enabled = Settings::RecoilControl;
    cfg->get<slider_t>("RCS Strength").callback = Settings::RcsStrength;
    cfg->get<checkbox_t>("Triggerbot").enabled = Settings::Triggerbot;
    cfg->get<slider_t>("Trigger Delay").callback = (float)Settings::TriggerDelay;
    cfg->get<dropdown_t>("Target Bone").callback = Settings::AimBone;
    cfg->get<slider_t>("FOV").callback = Settings::AimFov;
    cfg->get<slider_t>("Smooth").callback = Settings::AimSmooth;

    auto& aimBinds = cfg->get<checkbox_t>("Enable Aimbot").keybinds_list;
    int imguiAimKey = VKToImGuiKey(Settings::AimKey);
    aimBinds.clear();
    if (imguiAimKey != ImGuiKey_None)
        aimBinds.push_back({ 0, imguiAimKey, 2 });

    cfg->get<checkbox_t>("Box ESP").enabled = Settings::BoxEsp;
    cfg->get<checkbox_t>("Corner Box").enabled = Settings::CornerBox;
    cfg->get<checkbox_t>("3D Box").enabled = Settings::Box3D;
    cfg->get<checkbox_t>("Skeleton").enabled = Settings::Skeleton;
    cfg->get<checkbox_t>("Head Box").enabled = Settings::HeadBox;
    cfg->get<checkbox_t>("Body Dot").enabled = Settings::BodyDot;
    cfg->get<checkbox_t>("Health Bar").enabled = Settings::HealthBar;
    cfg->get<checkbox_t>("Snaplines").enabled = Settings::Snaplines;
    cfg->get<checkbox_t>("Distance").enabled = Settings::Distance;
    cfg->get<checkbox_t>("Team Check").enabled = Settings::TeamCheck;
    cfg->get<checkbox_t>("Visible Check").enabled = Settings::VisibilityCheck;
    cfg->get<checkbox_t>("Ignore Dormant").enabled = Settings::IgnoreDormant;
    cfg->get<checkbox_t>("Memory Radar").enabled = Settings::MemoryRadar;
    cfg->get<checkbox_t>("Spike Timer").enabled = Settings::SpikeTimer;
    cfg->get<checkbox_t>("View Angle").enabled = Settings::ViewAngle;
    cfg->get<checkbox_t>("Agent Icons").enabled = Settings::AgentIcons;
    cfg->get<checkbox_t>("Rainbow Skeleton").enabled = Settings::RainbowSkeleton;
    cfg->get<slider_t>("ESP Thickness").callback = Settings::EspThickness;
    cfg->get<checkbox_t>("Legit ESP").enabled = Settings::LegitEsp;
    cfg->get<checkbox_t>("Watermark").enabled = Settings::Watermark;
    cfg->get<dropdown_t>("Legit Mode").callback = Settings::LegitMode;
    cfg->get<slider_t>("Legit Time").callback = (float)Settings::LegitTime;
    auto& binds = cfg->get<checkbox_t>("Legit ESP").keybinds_list;
    int imguiKey = VKToImGuiKey(Settings::LegitKey);
    binds.clear();
    if (imguiKey != ImGuiKey_None)
        binds.push_back({ 0, imguiKey, 2 });
}

static bool g_jfInit = false;

void Menu::Init(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swapChain, HWND hwnd) {
    if (g_jfInit) return;
    g_jfInit = true;
    var->dx.device = device;
    var->dx.ctx = ctx;
    var->dx.swap_chain = swapChain;
    var->winapi.hwnd = hwnd;
    cfg->init_config();

    std::string icons = ExeDir() + "icons\\";
    widgets->load_texture(icons + "background.png", &var->img.background);
    widgets->load_texture(icons + "user_logo.png", &var->img.user_logo);
    widgets->load_texture(icons + "logo.png", &var->img.logo);

    Menu::SyncToCfg();
}

void Menu::Draw() {
    if (!Menu::Open && !overlay_menu::g_open) return;
    gui->render();
    SyncFromCfg();
    overlay_menu::g_open = Menu::Open;

    if (g_esp_data && ipc_client::is_connected())
        ipc_client::send_settings(g_esp_data->settings);
}

namespace overlay_menu {
    void render() {
        Menu::Open = g_open;
        Menu::Draw();
    }
}
