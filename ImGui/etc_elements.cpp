#include "etc_elements.h"

namespace e_elements {

bool begin_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags) {
    ImGuiContext& g = *GImGui;
    ImGuiWindow* parent_window = g.CurrentWindow;

    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
             ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;

    const ImVec2 content_avail = GetContentRegionAvail();
    ImVec2 size = ImFloor(size_arg);
    if (size.x <= 0.0f) size.x = ImMax(content_avail.x, 1.0f);
    if (size.y <= 0.0f) size.y = ImMax(content_avail.y, 1.0f);

    // Custom background with dark theme
    PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.094f, 0.094f, 0.102f, 1.0f));
    PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 10));

    bool ret = BeginChildEx(name, id, size, border, flags);
    
    return ret;
}

bool begin_child(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags) {
    ImGuiWindow* window = GetCurrentWindow();
    return begin_child_ex(str_id, window->GetID(str_id), size, border, flags);
}

bool begin_child(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags) {
    return begin_child_ex(NULL, id, size, border, flags);
}

void end_child() {
    EndChild();
    PopStyleVar(2);
    PopStyleColor();
}

} // namespace e_elements
