#pragma once

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

extern ImFont* bold;
extern ImFont* medium;

namespace e_elements {

    inline ImVec4 accent     = ImVec4(0.52f, 0.27f, 0.85f, 1.f);
    inline float  fade_alpha = 1.f; // used only for draw-list primitives

    inline bool begin_child(const char* label,
                            ImVec2 size = ImVec2(0.f, 0.f),
                            bool   /*unused*/ = false,
                            ImGuiWindowFlags extra = 0)
    {
        using namespace ImGui;

        // style.Alpha is set to fade_alpha by menu() — no override here.
        PushStyleColor(ImGuiCol_ChildBg,       ImVec4(0.094f, 0.094f, 0.102f, 1.f));
        PushStyleColor(ImGuiCol_Border,        ImVec4(1.f,    1.f,    1.f,    0.06f));
        PushStyleColor(ImGuiCol_ScrollbarBg,   ImVec4(0.f,    0.f,    0.f,    0.f));
        PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.52f,  0.27f,  0.85f,  0.35f));
        // 4 colors

        PushStyleVar(ImGuiStyleVar_ChildRounding, 6.f);
        PushStyleVar(ImGuiStyleVar_ItemSpacing,   ImVec2(8.f, 7.f));
        PushStyleVar(ImGuiStyleVar_ScrollbarSize, 5.f);
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 8.f));
        // 4 vars

        bool has_label = label && label[0] != '#';
        const float HEADER_H = has_label ? 24.f : 0.f;
        if (has_label && size.y > 0.f) size.y -= HEADER_H;

        const float fa = fade_alpha;
        ImVec2 csp = GetCursorScreenPos();

        if (has_label) {
            ImDrawList* pdl   = GetWindowDrawList();
            ImFont*     fnt   = bold ? bold : GetFont();
            const float fs    = fnt->FontSize * 0.80f;
            const float bar_w = size.x > 0.f ? size.x : GetContentRegionAvail().x;

            pdl->AddRectFilled(csp,
                ImVec2(csp.x + bar_w, csp.y + HEADER_H),
                GetColorU32(ImVec4(0.07f, 0.07f, 0.08f, 0.92f * fa)),
                6.f, ImDrawFlags_RoundCornersTop);
            pdl->AddLine(
                ImVec2(csp.x, csp.y + HEADER_H - 0.5f),
                ImVec2(csp.x + bar_w, csp.y + HEADER_H - 0.5f),
                GetColorU32(ImVec4(accent.x, accent.y, accent.z, 0.25f * fa)), 1.f);
            float ty = csp.y + (HEADER_H - fs) * 0.5f;
            pdl->AddText(fnt, fs, ImVec2(csp.x + 10.f, ty),
                GetColorU32(ImVec4(accent.x, accent.y, accent.z, 0.90f * fa)), label);
            float lw  = fnt->CalcTextSizeA(fs, FLT_MAX, 0.f, label).x;
            float rx0 = csp.x + 14.f + lw, rx1 = csp.x + bar_w - 8.f;
            if (rx1 > rx0 + 8.f)
                pdl->AddLine(ImVec2(rx0, csp.y + HEADER_H * 0.5f),
                             ImVec2(rx1, csp.y + HEADER_H * 0.5f),
                             GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.04f * fa)));
            SetCursorScreenPos(ImVec2(csp.x, csp.y + HEADER_H));
        }

        bool ret = BeginChild(label, size, true, ImGuiWindowFlags_None | extra);
        return ret;
    }

    inline void end_child()
    {
        ImGui::EndChild();
        ImGui::PopStyleVar(4);
        ImGui::PopStyleColor(4);
    }

} // namespace e_elements
