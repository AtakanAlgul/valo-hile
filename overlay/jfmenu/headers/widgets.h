#pragma once
#include "includes.h"
#include "../headers/config.h"

#define IMGUI_DEFINE_MATH_OPERATORS

struct popup_data_t
{
    std::string name{};
    c_id owner_window_id{};
    bool open{ false };
    float alpha{ 0.f };
};

inline std::string const keys[] = { "Tab", "Left", "Right", "Up", "Down", "Page Up", "Page Down", "Home", "End", "Insert", "Delete", "Backspace", "Space", "Enter", "Escape", "Ctrl", "Shift", "Alt", "Super", "Ctrl", "Shift", "Alt", "Super", "Menu", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", "Apostrophe", "Comma", "Minus", "Period", "Slash", "Semicolon", "Equal", "Left Bracket", "Backslash", "Right Bracket", "Grave Accent", "Caps Lock", "Scroll Lock", "Num Lock", "Print Screen", "Pause", "Keypad 0", "Keypad 1", "Keypad 2", "Keypad 3", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad 7", "Keypad 8", "Keypad 9", "Keypad .", "Keypad /", "Keypad *", "Keypad -", "Keypad +", "Keypad Enter", "Keypad =", "App Back", "App Forward", "Gamepad Start", "Gamepad Back", "Gamepad Face Left", "Gamepad Face Right", "Gamepad Face Up", "Gamepad Face Down", "Gamepad Dpad Left", "Gamepad Dpad Right", "Gamepad Dpad Up", "Gamepad Dpad Down", "Gamepad L1", "Gamepad R1", "Gamepad L2", "Gamepad R2", "Gamepad L3", "Gamepad R3", "Gamepad L Stick Left", "Gamepad L Stick Right", "Gamepad L Stick Up", "Gamepad L Stick Down", "Gamepad R Stick Left", "Gamepad R Stick Right", "Gamepad R Stick Up", "Gamepad R Stick Down", "Mouse 1", "Mouse 2", "Mouse 3", "Mouse 4", "Mouse 5", "Mouse Wheel X", "Mouse Wheel Y", "Ctrl", "Shift", "Alt", "Super" };

inline std::string get_key_name(ImGuiKey key)
{
    if (key == ImGuiKey_None)
        return "None";

    return keys[key - ImGuiKey_NamedKey_BEGIN];
}

inline std::string utf8_safe_truncate(const std::string& str, size_t max_chars)
{
    size_t i = 0;       
    size_t char_count = 0;

    while (i < str.size() && char_count < max_chars)
    {
        unsigned char c = static_cast<unsigned char>(str[i]);

        size_t char_size = 1;

        if ((c & 0x80) == 0x00)         char_size = 1; // ASCII
        else if ((c & 0xE0) == 0xC0)    char_size = 2; // 2 байта
        else if ((c & 0xF0) == 0xE0)    char_size = 3; // 3 байта
        else if ((c & 0xF8) == 0xF0)    char_size = 4; // 4 байта

        if (i + char_size > str.size())
            break;

        i += char_size;
        char_count++;
    }

    std::string result = str.substr(0, i);

    if (i < str.size())
        result += "...";

    return result;
}

inline bool need_sep()
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    float cursor_y = window->DC.CursorPos.y - window->DC.CursorStartPos.y;
    float content_bottom_y = window->ContentSize.y;

    float avail = content_bottom_y - cursor_y;

    avail = ImMax(avail, 0.0f);

    return avail > 1.0f;
}

struct config_button_t {
    bool pressed, share, download, edit, del;
};

struct config_t {
    int idx;
    std::string name, date;
};

class c_widgets
{
public:
    std::vector<popup_data_t> popup_storage;
    std::vector<config_t> config_storage;
    int config_idx = 0;
    int keybind_idx = 0;
    void open_popup(std::string name);
    void close_popup(std::string name);
    bool is_popup_open(std::string name);
    bool popup(std::string name, c_vec2 size, c_vec2 pos = { 0, 0 }, c_vec2 padding = { 0, 0 }, c_vec2 spacing = { 0, 0 }, float rounding = 0.f, bool always_on_screen = false, window_flags flags = 0);
    void end_popup();
    void load_texture(std::string path, ImTextureID* img);
    bool tab_button(std::string name, std::string icon, bool is_active);
    bool subtab_section(std::string name, bool is_active, std::vector<subtab_t>* subtabs_list);
    void draw_segment(ImDrawList* draw_list, c_vec2 center, ImU32 col);
    void child(std::string icon, std::string name, c_vec2 padding = { -1, -1 });
    void end_child();
    bool checkbox(std::string name);
    void seperator();
    bool slider(std::string name);
    bool dropdown(std::string name);
    bool multi_dropdown(std::string name);
    bool selectable(std::string name, bool is_selected);
    bool curve(std::string name, float* first_x, float* first_y, float* second_x, float* second_y);
    bool weapon_checkbox(std::string checkbox_data_name, std::string weapon_name, std::string class_name, ImTextureID weapon, c_vec2 weapon_image_size);
    void keybind(std::string name, c_rect rect, bool pressed, std::vector<keybind_t>* keybinds_list);
    void init_keybinds();
    void blackout();
    void weapon_info(std::string name, bool* open, std::string weapon_class, std::string weapon_name, ImTextureID weapon_img, c_vec2 weapon_img_size, std::string ammo, std::string scope, std::string barrel);
    config_button_t config_button(int idx, std::string name, std::string date, bool loaded);
    void config_info(std::string icon, std::string name, std::string info);
    void colorpicker(std::string name, c_vec4* color, bool alpha = false);
    bool text_field_ex(std::string_view label, std::string_view hint, char* buf, int buf_size, float text_padding, float line_padding, ImU32 text_col, bool centered, const ImRect& rect, bool* active, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* callback_user_data, bool user_clicked);
    bool search(std::string name);
    bool config_field(std::string name, char* buf, size_t buf_size);
};

inline std::unique_ptr<c_widgets> widgets = std::make_unique<c_widgets>();

enum notify_type
{
    success = 0,
    warning = 1,
    error = 2
};

struct notify_state
{
    int notify_id;
    std::string_view text;
    notify_type type{ success };

    ImVec2 window_size{ 0, 0 };
    float notify_alpha{ 0 };
    bool active_notify{ true };
    float notify_timer{ 0 };
    float notify_pos{ 0 };
};

class c_notify
{
public:
    void setup_notify();

    void add_notify(std::string_view text, notify_type type);

private:
    ImVec2 render_notify(int cur_notify_value, float notify_alpha, float notify_percentage, float notify_pos, std::string_view text, notify_type type);

    float notify_time{ 15 };
    int notify_count{ 0 };

    float notify_spacing{ 20 };
    ImVec2 notify_padding{ 20, 20 };

    std::vector<notify_state> notifications;

};

inline std::unique_ptr<c_notify> notify = std::make_unique<c_notify>();
