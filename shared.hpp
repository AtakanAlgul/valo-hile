#pragma once
#include <cstdint>
#include <Windows.h>

#define MAX_PLAYERS  64
#define MAX_BONES    14

#pragma pack(push, 1)

struct BonePoint2D {
    float x, y;
    bool  valid;
};

struct PlayerESP {
    bool        valid;
    bool        visible;
    bool        alive;
    bool        is_teammate;   // team check flag
    float       head_x,   head_y;
    float       foot_x,   foot_y;
    float       box_left, box_top, box_right, box_bottom;
    float       health;
    float       shield;
    float       distance;
    char        name[32];
    BonePoint2D bones[MAX_BONES];
    bool        box3d_valid;
    BonePoint2D box3d[8];
};

struct SharedSettings {
    bool  box2d          = false;
    bool  corner         = true;
    bool  box3d          = false;
    bool  sk3let0n       = true;
    bool  h3althbar      = true;
    bool  headb0x        = false;
    bool  snapline       = false;
    bool  vischeck       = false;
    float esp_thickness  = 1.0f;
    float vis_r = 1.0f, vis_g = 0.0f, vis_b = 0.0f, vis_a = 1.0f;
    float invis_r = 1.0f, invis_g = 1.0f, invis_b = 1.0f, invis_a = 1.0f;
    bool  a1mbot         = true;
    bool  a1m_v1sh_ch3ck = true;
    bool  reco1l_contr0l = true;
    bool  draw_f0v       = true;
    float a1m_sm00th     = 10.0f;
    float a1m_f0v        = 40.0f;
    int   a1m_b0ne       = 0;
    int   a1m_k3y        = 0x01;
    bool  filled_f0v     = false;
    bool  tr1ggerbot     = false;
    int   fl1ck_delay    = 90;
    float rcs_strength   = 0.6f;
    // Team check
    bool  t3am_check     = true;
    float team_r = 0.0f, team_g = 1.0f, team_b = 0.0f, team_a = 1.0f;
    // Extra visuals
    bool  player_dist    = true;
    bool  dormant        = true;
    bool  spiketimer     = false;
    bool  radar          = false;
    bool  view_angle     = false;
    bool  agent_icons    = false;
    bool  rainbow_skel   = false;
};

// ─── Doğrudan Bellek Durumu (Tek DLL / Sıfır Şifreleme) ──────────────────────
struct SharedESPData {
    bool           overlay_connected;
    float          screen_w;
    float          screen_h;
    int32_t        player_count;
    bool           menu_open;
    SharedSettings settings;
    PlayerESP      players[MAX_PLAYERS];
};

#pragma pack(pop)

// Global işaretçi — aynı process içinde doğrudan bellek erişimi
inline SharedESPData* g_esp_data = nullptr;
