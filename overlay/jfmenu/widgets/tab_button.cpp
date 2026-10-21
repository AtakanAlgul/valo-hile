#include "../headers/includes.h"

struct tab_button_state_t {
    c_vec4 text;
    float alpha;
};

bool c_widgets::tab_button(std::string name, std::string icon, bool is_active)
{
    c_window* window = gui->get_window();
    c_id id = window->GetID(name.data());
    tab_button_state_t* state = gui->anim_container<tab_button_state_t>(id);

    c_vec2 pos = window->DC.CursorPos;
    c_vec2 size = { gui->content_avail().x, SCALE(33) };
    c_rect rect = { pos, pos + size };

    gui->item_size(rect);
    gui->item_add(rect, id);

    bool hover, held, pressed = gui->button_behavior(rect, id, &hover, &held, ImGuiButtonFlags_PressedOnClick);

    gui->easing(state->alpha, is_active ? 1.f : 0.f, 7.f, static_easing);
    gui->easing(state->text, is_active ? clr->white.Value : clr->text.Value, 16.f, dynamic_easing);

    draw->rect_filled(var->tab.draw_list, rect.Min, rect.Max, draw->get_clr(clr->tab_layout, 0.45f * state->alpha), SCALE(6));
    if (state->alpha > 0.05f)
        draw->rect(var->tab.draw_list, rect.Min, rect.Max, draw->get_clr(clr->border, 0.4f * state->alpha), SCALE(6), 0, SCALE(1.f));
    draw->text_clipped(var->tab.draw_list, font->get(icons, 14), rect.Min + SCALE(10, 0), rect.Max, draw->get_clr(state->text), icon.data(), 0, 0, { 0, 0.5 });
    draw->text_clipped(var->tab.draw_list, font->get(sf_pro, 12), rect.Min + SCALE(34, 0), rect.Max, draw->get_clr(state->text), name.data(), 0, 0, { 0, 0.5 });

    return pressed;
}