#pragma once

#include "widgets_colors.h"

namespace settings {

    inline ImVec2 size_menu = ImVec2(700, 520);
    inline ImVec2 size_watermark = ImVec2(400, 35);
    inline ImVec2 size_preview = ImVec2(300, 400);
    inline ImVec2 item_spacing = ImVec2(0, 0);
    inline ImVec2 item_padding = ImVec2(0, 0);

    inline const char* cheat_name = "RENAGLOBAL";
    inline const char* developer = "RENA";

}

namespace misc {

    inline int tab_count = 0;
    inline int active_tab_count = 0;

    inline float anim_tab = 0;

    inline int tab_width = 85;

    inline float child_add = 0;
    inline float alpha_child = 0;

}

namespace menu {

    inline ImVec4 window_bg = ImColor(18, 19, 21);
    inline ImVec4 border = ImColor(0, 0, 0, 0);
    inline ImVec4 border_shadow = ImColor(0, 0, 0, 0);
    inline ImVec4 general_child = ImColor(23, 23, 25);
    inline ImVec4 scrollbar = ImColor(30, 31, 33);
    inline ImVec4 scrollbar_hovered = ImColor(30, 31, 33);
    inline ImVec4 scrollbar_bg = ImColor(18, 19, 21);
    inline ImVec4 watermark_bg = ImColor(17, 18, 20);
    inline ImVec4 watermark_border = ImColor(17, 18, 20, 0);
    inline ImVec4 watermark_filled = ImColor(27, 25, 28);
    inline ImVec4 watermark_name = ImColor(255, 255, 255);
    inline ImVec4 line = ImColor(23, 24, 26);
    inline ImVec4 text = ImColor(140, 141, 143);
    inline ImVec4 line2 = ImColor(12, 13, 15);
    inline float window_rounding = 3.f;
    inline float scroll_size = 10.f;

}

#include <d3d11.h>

namespace pictures {
    inline ID3D11ShaderResourceView* aim_img = nullptr;
    inline ID3D11ShaderResourceView* visual_img = nullptr;
    inline ID3D11ShaderResourceView* setting_img = nullptr;
}

namespace fonts {

    inline ImFont* sans_font = nullptr;
    inline ImFont* sans_font_small = nullptr;
    inline ImFont* weapon_font = nullptr;
}

namespace features {

    inline bool check1, check2, check3, check4, check5;
    inline bool check6 = true;
    inline bool check7 = true;

    inline bool check8, check9, check10, check11, check12, check13;

    inline int sliderint, sliderint2, sliderint3, sliderint4;

    inline int selectedItem = 0;
    inline int selected = 0;

    inline const char* items[]{ "Value", "Random" };

    inline const char* items_count[]{ "Combo1", "Combo2", "Combo3", "Combo4" };

    inline ImVec4 fov_color = ImColor(60, 157, 173);

    inline int key = 0, var = 0;

    inline int key2 = 0, var2 = 0;

    inline int key3 = 0, var3 = 0;

    inline char input[64] = { "" };

    inline bool multi[5] = { false, true, true, false, true };

    inline const char* multi_items[5] = { "Head", "Chest", "Stromatch", "Body", "Legs" };

    inline bool multi_esp[7] = { false, false, false, false, false, false, false };

    inline const char* multi_preview[7] = { "Box", "Health", "Armor", "Nickname", "Distance", "Weapon", "Skeleton" };

    inline bool esp_perview;

    inline float preview_alpha;
}

inline void ShadowText(ImFont* font, const char* text, ImVec2 pos, ImVec2 rel, ImColor color, bool outline, float size) {
    float dpiscale = 1.50f;
    float relx = 0;
    float rely = 0;
    switch ((int)rel.x) {
    case 0:
        relx = (ImGui::CalcTextSize(text).x / (19 * dpiscale) * (size * dpiscale)) / 2;
        break;
    case 1:
        relx = 0;
        break;
    case -1:
        relx = (ImGui::CalcTextSize(text).x / (19 * dpiscale) * (size * dpiscale));
        break;
    }
    switch ((int)rel.y) {
    case 0:
        rely = (ImGui::CalcTextSize(text).y / (22 * dpiscale) * (size * dpiscale)) / 2;
        break;
    case 1:
        rely = 0;
        break;
    case -1:
        rely = (ImGui::CalcTextSize(text).y / (22 * dpiscale) * (size * dpiscale));
        break;
    }
    if (outline) {
        ImGui::GetWindowDrawList()->AddText(font, size * dpiscale, ImVec2(pos.x - relx - 1, pos.y - rely - 1), ImColor(0, 0, 0), text);
        ImGui::GetWindowDrawList()->AddText(font, size * dpiscale, ImVec2(pos.x - relx + 1, pos.y - rely - 1), ImColor(0, 0, 0), text);
        ImGui::GetWindowDrawList()->AddText(font, size * dpiscale, ImVec2(pos.x - relx - 1, pos.y - rely + 1), ImColor(0, 0, 0), text);
        ImGui::GetWindowDrawList()->AddText(font, size * dpiscale, ImVec2(pos.x - relx + 1, pos.y - rely + 1), ImColor(0, 0, 0), text);
        ImGui::GetWindowDrawList()->AddText(font, size * dpiscale, ImVec2(pos.x - relx, pos.y - rely), color, text);
    }
}
