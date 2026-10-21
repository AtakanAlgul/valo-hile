#pragma once

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "etc_elements.h"  // e_elements::accent

extern ImFont* tab_icons;
extern ImFont* medium;

namespace elements {

    // ─── Sidebar icon tab button (39×39) ────────────────────────────────────
    inline bool tab(const char* icon, bool active)
    {
        ImGuiWindow* win = ImGui::GetCurrentWindow();
        if (win->SkipItems) return false;

        const ImGuiID id   = win->GetID(icon);
        const ImVec2  sz   = ImVec2(39.f, 39.f);
        const ImVec2  pos  = win->DC.CursorPos;
        const ImRect  bb(pos, pos + sz);

        ImGui::ItemSize(sz);
        if (!ImGui::ItemAdd(bb, id)) return false;

        bool hov, held;
        const bool pressed = ImGui::ButtonBehavior(bb, id, &hov, &held);

        ImDrawList* dl = win->DrawList;
        const ImVec4& ac = e_elements::accent;

        float& anim = *ImGui::GetStateStorage()->GetFloatRef(id, active ? 1.f : 0.f);
        anim = ImLerp(anim, active ? 1.f : (hov ? 0.45f : 0.f),
                      ImGui::GetIO().DeltaTime * 12.f);

        // background pill
        if (anim > 0.01f) {
            ImU32 bg = ImGui::GetColorU32(ImVec4(ac.x, ac.y, ac.z, 0.13f * anim));
            dl->AddRectFilled(bb.Min, bb.Max, bg, 6.f);
        }

        // left accent bar (active only)
        if (active) {
            float bh = (sz.y - 14.f) * anim;
            float cy = bb.Min.y + sz.y * 0.5f;
            dl->AddRectFilled(
                ImVec2(bb.Min.x, cy - bh * 0.5f),
                ImVec2(bb.Min.x + 3.f, cy + bh * 0.5f),
                ImGui::GetColorU32(ImVec4(ac.x, ac.y, ac.z, anim)),
                1.5f);
        }

        // icon
        ImFont* fnt = tab_icons ? tab_icons : ImGui::GetFont();
        ImVec2  isz = fnt->CalcTextSizeA(fnt->FontSize, FLT_MAX, 0.f, icon);
        ImVec2  ipos = ImVec2(bb.Min.x + (sz.x - isz.x) * 0.5f,
                              bb.Min.y + (sz.y - isz.y) * 0.5f);

        float br = 0.38f + 0.62f * anim;
        ImU32 icol = active
            ? ImGui::GetColorU32(ImVec4(ac.x, ac.y, ac.z, 1.f))
            : ImGui::GetColorU32(ImVec4(br, br, br, 1.f));

        dl->AddText(fnt, fnt->FontSize, ipos, icol, icon);

        return pressed;
    }

    // ─── Sub-tab text button ─────────────────────────────────────────────────
    inline bool subtab(const char* name, bool active)
    {
        ImGuiWindow* win = ImGui::GetCurrentWindow();
        if (win->SkipItems) return false;

        ImFont* fnt = medium ? medium : ImGui::GetFont();
        const float fs   = fnt->FontSize;
        const ImVec2 pad = ImVec2(10.f, 5.f);
        const ImVec2 tsz = fnt->CalcTextSizeA(fs, FLT_MAX, 0.f, name);
        const ImVec2 sz  = tsz + pad * 2.f;

        const ImGuiID id  = win->GetID(name);
        const ImVec2  pos = win->DC.CursorPos;
        const ImRect  bb(pos, pos + sz);

        ImGui::ItemSize(sz);
        if (!ImGui::ItemAdd(bb, id)) return false;

        bool hov, held;
        const bool pressed = ImGui::ButtonBehavior(bb, id, &hov, &held);

        ImDrawList* dl = win->DrawList;
        const ImVec4& ac = e_elements::accent;

        float& anim = *ImGui::GetStateStorage()->GetFloatRef(id, active ? 1.f : 0.f);
        anim = ImLerp(anim, active ? 1.f : (hov ? 0.5f : 0.f),
                      ImGui::GetIO().DeltaTime * 12.f);

        if (anim > 0.01f)
            dl->AddRectFilled(bb.Min, bb.Max,
                              ImGui::GetColorU32(ImVec4(ac.x, ac.y, ac.z, 0.14f * anim)),
                              4.f);

        float tr = active ? 1.f : ImLerp(0.45f, 0.75f, anim);
        ImU32 tcol = ImGui::GetColorU32(ImVec4(tr, tr, tr, 1.f));
        dl->AddText(fnt, fs, bb.Min + pad, tcol, name);

        return pressed;
    }

} // namespace elements
