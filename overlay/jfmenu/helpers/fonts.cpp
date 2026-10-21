#include "../headers/includes.h"
#include "imgui_impl_dx11.h"
#include "../../../Assets/fonthelper.h"
#include "../../../Assets/icons.h"

// classic default font handle for ESP overlay text (rebuilt with the atlas)
ImFont* g_espFont = nullptr;
extern ImFont* AVERISONTOP;
extern ImFont* WeaponIconFont;

void c_font::init_defaults()
{
    add(syne, 22);
    add(sf_pro, 11);
    add(sf_pro, 12);
    add(sf_pro, 13);
    add(icons, 10);
    add(icons, 11);
    add(icons, 12);
    add(icons, 14);
    add(icons, 16);
    var->gui.dpi_changed = true;
}

void c_font::update()
{
    if (var->gui.dpi_changed)
    {
        var->gui.dpi = var->gui.stored_dpi / 100.f;

        ImFontConfig cfg;
        cfg.FontDataOwnedByAtlas = false;

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Clear();

        for (auto& font_t : data)
        {
            font_t.font = io.Fonts->AddFontFromMemoryTTF(font_t.data.data(), (int)font_t.data.size(), SCALE(font_t.size), &cfg, io.Fonts->GetGlyphRangesCyrillic());
        }

        // classic default font for ESP overlay text (old UI look)
        g_espFont = io.Fonts->AddFontDefault();

        // Game ESP fonts
        AVERISONTOP = io.Fonts->AddFontFromMemoryTTF((void*)font_binary, sizeof(font_binary), 16.f, &cfg);

        ImFontConfig wfc;
        wfc.OversampleH = 3; wfc.OversampleV = 3; wfc.PixelSnapH = false;
        wfc.FontDataOwnedByAtlas = false;
        WeaponIconFont = io.Fonts->AddFontFromMemoryTTF((void*)ValorantGunIcons, sizeof(ValorantGunIcons), 20.f, &wfc);

        io.Fonts->Build();
        io.FontDefault = g_espFont;
        ImGui_ImplDX11_CreateDeviceObjects();

        var->gui.dpi_changed = false;
    }
}

ImFont* c_font::get(std::vector<unsigned char> font_data, float size)
{
    for (auto& font_item : data)
    {
        if (font_item.data == font_data && font_item.size == size)
        {
            if (font_item.font != nullptr)
                return font_item.font;
        }
    }

    add(font_data, size);
    var->gui.dpi_changed = true;
    update();

    for (auto& font_item : data)
    {
        if (font_item.data == font_data && font_item.size == size)
        {
            if (font_item.font != nullptr)
                return font_item.font;
        }
    }

    if (g_espFont) return g_espFont;
    if (AVERISONTOP) return AVERISONTOP;
    return ImGui::GetFont();
}

void c_font::add(std::vector<unsigned char> font_data, float size)
{
    data.push_back({ font_data, size, nullptr });
}