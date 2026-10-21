#include "nav_elements.h"

namespace elements {

bool tab(const char* icon, bool boolean) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(icon);
    const ImVec2 label_size = CalcTextSize(icon, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImVec2(39, 39);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_None);

    bool changed = false;
    if (pressed && !boolean) {
        changed = true;
    }

    // Draw background
    ImDrawList* draw = window->DrawList;
    ImU32 bg_col = boolean ? GetColorU32(ImVec4(0.576f, 0.745f, 0.259f, 0.15f)) 
                           : (hovered ? GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.05f)) 
                                      : GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 0.0f)));
    
    if (bg_col & IM_COL32_A_MASK) {
        draw->AddRectFilled(bb.Min, bb.Max, bg_col, 4.0f);
    }

    // Left accent bar when active
    if (boolean) {
        draw->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y + 4), 
                           ImVec2(bb.Min.x + 3, bb.Max.y - 4), 
                           GetColorU32(ImVec4(0.576f, 0.745f, 0.259f, 1.0f)), 
                           2.0f);
    }

    // Draw icon
    ImFont* font = tab_icons ? tab_icons : GetFont();
    ImVec2 icon_size = CalcTextSize(icon, NULL, true);
    ImVec2 icon_pos = ImVec2(bb.Min.x + (size.x - icon_size.x) * 0.5f,
                             bb.Min.y + (size.y - icon_size.y) * 0.5f);
    ImU32 text_col = boolean ? GetColorU32(ImVec4(0.576f, 0.745f, 0.259f, 1.0f)) 
                             : GetColorU32(ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
    draw->AddText(font, font->FontSize, icon_pos, text_col, icon);

    return changed;
}

bool subtab(const char* name, bool boolean) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = CalcTextSize(name, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 padding = ImVec2(12, 6);
    ImVec2 size = ImVec2(label_size.x + padding.x * 2, label_size.y + padding.y * 2);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_None);

    bool changed = false;
    if (pressed && !boolean) {
        changed = true;
    }

    ImDrawList* draw = window->DrawList;
    
    // Background for active
    if (boolean) {
        draw->AddRectFilled(bb.Min, bb.Max, GetColorU32(ImVec4(0.576f, 0.745f, 0.259f, 0.15f)), 4.0f);
    }

    // Text
    ImU32 text_col = boolean ? GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)) 
                             : GetColorU32(ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
    draw->AddText(bb.Min + padding, text_col, name);

    return changed;
}

} // namespace elements
