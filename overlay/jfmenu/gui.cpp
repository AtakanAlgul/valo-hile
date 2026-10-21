#include "headers/includes.h"
#include "../Menu.h"

void c_gui::render()
{
	if (var->tab.tab_stored >= (int)var->tab.list.size())
		var->tab.tab_stored = 0;
	if (var->tab.tab_current >= (int)var->tab.list.size())
		var->tab.tab_current = 0;

	bool tab_changed = var->tab.tab_current != var->tab.tab_stored || var->tab.subtab_current != var->tab.subtab_stored || var->tab.item_current != var->tab.item_stored;

	gui->easing(var->tab.alpha, tab_changed ? 0.f : 1.f, 7.f, static_easing);
	if (var->tab.alpha == 0)
	{
		if (var->tab.tab_current != var->tab.tab_stored)
		{
			var->tab.item_current = 0; var->tab.item_stored = 0;
			var->tab.subtab_current = 0; var->tab.subtab_stored = 0;
			var->tab.tab_current = var->tab.tab_stored;
		}
			
		if (var->tab.subtab_current != var->tab.subtab_stored)
		{
			var->tab.item_current = 0; var->tab.item_stored = 0;
			var->tab.subtab_current = var->tab.subtab_stored;
		}

		if (var->tab.item_current != var->tab.item_stored)
			var->tab.item_current = var->tab.item_stored;
	}

	if (IsKeyPressed(ImGuiKey_F1))
	{
		var->gui.stored_dpi += 10;
		var->gui.dpi_changed = true;
	}
	if (IsKeyPressed(ImGuiKey_F2))
	{
		var->gui.stored_dpi -= 10;
		var->gui.dpi_changed = true;
	}

	widgets->init_keybinds();

	var->blackout.active = false;

	gui->initialize();
	gui->set_next_window_size(SCALE(elements->window.size));
	gui->begin(elements->window.name, nullptr, window_flags_no_scrollbar | window_flags_no_scroll_with_mouse | window_flags_no_bring_to_front_on_focus | window_flags_no_focus_on_appearing | window_flags_no_background | window_flags_no_decoration);
	{
		gui->set_style();
		gui->draw_decorations();

		gui->begin_content("nav", SCALE(elements->nav.size), { 0, 0 }, { 0, 0 }, window_flags_no_scrollbar | window_flags_no_scroll_with_mouse);
		{	
			gui->dummy({ gui->content_avail().x, SCALE(55) });
			draw->text_clipped(gui->window_drawlist(), font->get(syne, 22), GetItemRectMin(), GetItemRectMax(), draw->get_clr(clr->white), "V-CORE", 0, 0, { 0.5, 0.5 });
			
			gui->begin_content("tabs", gui->content_avail(), SCALE(12, 0), { 0, 0 }, window_flags_no_scroll_with_mouse | window_flags_no_scrollbar | window_flags_no_move);
			{
				var->tab.draw_list = gui->window_drawlist();

				for (int i = 0; i < var->tab.list.size(); ++i)
				{
					tab_t tab = var->tab.list[i];

					if (widgets->tab_button(tab.name, tab.icon, var->tab.tab_stored == i))
					{
						var->tab.tab_stored = i;
					}
					if (tab.subtabs_list.size() > 0)
					{
						widgets->subtab_section(tab.name, var->tab.tab_stored == i, &var->tab.list[i].subtabs_list);
					}
				}
			}
			gui->end_content();
		}
		gui->end_content();

		gui->sameline();

		gui->begin_content("content", SCALE(elements->content.size), SCALE(elements->content.padding), SCALE(elements->content.padding), window_flags_no_scrollbar | window_flags_no_scroll_with_mouse);
		{
			gui->begin_content("header", { gui->content_avail().x, SCALE(34) }, SCALE(0, 0), SCALE(0, 0));
			{
				c_rect rect = gui->get_window()->Rect();

				// Status badge on the left
				c_vec2 badge_pos = rect.Min + SCALE(4, 6);
				c_vec2 badge_size = SCALE(78, 22);
				c_rect badge_rect = { badge_pos, badge_pos + badge_size };
				draw->rect_filled(gui->window_drawlist(), badge_rect.Min, badge_rect.Max, draw->get_clr(clr->child), SCALE(6));
				draw->rect(gui->window_drawlist(), badge_rect.Min, badge_rect.Max, draw->get_clr(clr->border, 0.45f), SCALE(6), 0, SCALE(1.f));
				draw->circle_filled(gui->window_drawlist(), badge_rect.Min + SCALE(10, 11), SCALE(3.5f), draw->get_clr({ 70, 200, 120, 255 }));
				draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 11), badge_rect.Min + SCALE(19, 0), badge_rect.Max, draw->get_clr(clr->white), "ACTIVE", 0, 0, { 0.1f, 0.5f });

				// Right side: Brand & Toggle badge
				draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 13), rect.Min, rect.Max - SCALE(6, 6), draw->get_clr(clr->white), "V-core", 0, 0, { 1, 0.15f });
				draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 11), rect.Min, rect.Max - SCALE(6, 0), draw->get_clr(clr->text), "Press INSERT", 0, 0, { 1, 0.9f });
			}
			gui->end_content();

			gui->begin_content("nav_info", { gui->content_avail().x, SCALE(20) }, SCALE(0, 0), SCALE(0, 0));
			{
				c_rect rect = gui->get_window()->Rect();

				gui->push_var(style_var_alpha, var->tab.alpha);

				std::string tab_name = var->tab.list[var->tab.tab_current].name;
				c_vec2 tab_name_size = gui->text_size(font->get(sf_pro, 12), tab_name.data());

				draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 12), rect.Min, rect.Max, draw->get_clr(clr->text), tab_name.data(), 0, 0, { 0, 0.5 });

				std::string subtab_name;
				c_vec2 subtab_name_size;
				if (!var->tab.list[var->tab.tab_current].subtabs_list.empty() && var->tab.list[var->tab.tab_current].subtabs_list.size() > 0)
				{
					subtab_name = var->tab.list[var->tab.tab_current].subtabs_list[var->tab.subtab_current].name;
					
					draw->text_clipped(gui->window_drawlist(), font->get(icons, 10), rect.Min + c_vec2{ tab_name_size.x + SCALE(10), 0 }, rect.Max, draw->get_clr(clr->text), "N", 0, 0, { 0, 0.5 });

					draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 12), rect.Min + c_vec2{ tab_name_size.x + SCALE(30), 0 }, rect.Max, draw->get_clr(clr->text), subtab_name.data(), 0, 0, { 0, 0.5 });
					
					subtab_name_size = gui->text_size(font->get(sf_pro, 12), subtab_name.data());

					std::string item_name;
					if (!var->tab.list[var->tab.tab_current].subtabs_list[var->tab.subtab_current].weapons_list.empty() && var->tab.list[var->tab.tab_current].subtabs_list[var->tab.subtab_current].weapons_list.size() > 0)
					{
						item_name = var->tab.list[var->tab.tab_current].subtabs_list[var->tab.subtab_current].weapons_list[var->tab.item_current];

						draw->text_clipped(gui->window_drawlist(), font->get(icons, 10), rect.Min + c_vec2{ tab_name_size.x + subtab_name_size.x + SCALE(40), 0 }, rect.Max, draw->get_clr(clr->text), "N", 0, 0, { 0, 0.5 });

						draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 12), rect.Min + c_vec2{ tab_name_size.x + subtab_name_size.x + SCALE(60), 0 }, rect.Max, draw->get_clr(clr->text), item_name.data(), 0, 0, { 0, 0.5 });
					}
				}

				gui->pop_var();

				draw->text_clipped(gui->window_drawlist(), font->get(sf_pro, 12), rect.Min, rect.Max, draw->get_clr(clr->text), "v1.0", 0, 0, { 1, 0.5 });
			}
			gui->end_content();

			gui->push_var(style_var_scrollbar_border_padding, { 0, 0 });
			gui->push_var(style_var_scrollbar_content_padding, SCALE(8));
			gui->push_var(style_var_scrollbar_size, SCALE(10));
			gui->push_var(style_var_alpha, var->tab.alpha);
		
			gui->begin_content("features", gui->content_avail(), SCALE(0, 0), SCALE(10, 10));
			{
				elements->child.width = (gui->content_avail().x - SCALE(10)) / 2;
				var->widget.draw_list = gui->window_drawlist();

				if (var->tab.tab_current == 0)
				{
					gui->begin_group();
					{
						widgets->child("K", "Aimbot");
						{
							widgets->checkbox("Enable Aimbot");
							widgets->checkbox("Draw FOV");
							widgets->checkbox("Filled FOV");
							widgets->checkbox("Visibility Check");
							widgets->checkbox("Recoil Control");
							widgets->slider("RCS Strength");
						}
						widgets->end_child();

						widgets->child("V", "Triggerbot");
						{
							widgets->checkbox("Triggerbot");
							widgets->slider("Trigger Delay");
						}
						widgets->end_child();
					}
					gui->end_group();

					gui->sameline();

					gui->begin_group();
					{
						widgets->child("D", "Targeting Settings");
						{
							widgets->dropdown("Target Bone");
							widgets->slider("FOV");
							widgets->slider("Smooth");
						}
						widgets->end_child();
					}
					gui->end_group();
				}

				if (var->tab.tab_current == 1)
				{
					if (var->tab.subtab_current == 0)
					{
						gui->begin_group();
						{
							widgets->child("D", "Player ESP");
							{
								widgets->checkbox("Box ESP");
								widgets->checkbox("Corner Box");
								widgets->checkbox("3D Box");
								widgets->checkbox("Skeleton");
								widgets->checkbox("Head Box");
								widgets->checkbox("Body Dot");
							}
							widgets->end_child();
						}
						gui->end_group();

						gui->sameline();

						gui->begin_group();
						{
							widgets->child("V", "Filters & Info");
							{
								widgets->checkbox("Health Bar");
								widgets->checkbox("Snaplines");
								widgets->checkbox("Distance");
								widgets->checkbox("Team Check");
								widgets->checkbox("Visible Check");
								widgets->checkbox("Ignore Dormant");
							}
							widgets->end_child();
						}
						gui->end_group();
					}
					else if (var->tab.subtab_current == 1)
					{
						gui->begin_group();
						{
							widgets->child("D", "Radar & Objectives");
							{
								widgets->checkbox("Memory Radar");
								widgets->checkbox("Spike Timer");
							}
							widgets->end_child();
						}
						gui->end_group();

						gui->sameline();

						gui->begin_group();
						{
							widgets->child("V", "Render Options");
							{
								widgets->checkbox("View Angle");
								widgets->checkbox("Agent Icons");
								widgets->checkbox("Rainbow Skeleton");
								widgets->slider("ESP Thickness");
							}
							widgets->end_child();
						}
						gui->end_group();
					}
					else
					{
						gui->begin_group();
						{
							widgets->child("H", "Legit ESP");
							{
								widgets->checkbox("Legit ESP");
								widgets->dropdown("Legit Mode");
								widgets->slider("Legit Time");
							}
							widgets->end_child();
						}
						gui->end_group();
					}
				}

				if (var->tab.tab_current == 2)
				{
					gui->begin_group();
					{
						widgets->child("D", "ESP Colors");
						{
							widgets->colorpicker("Box", reinterpret_cast<c_vec4*>(Settings::BoxColor), true);
							widgets->colorpicker("Snapline", reinterpret_cast<c_vec4*>(Settings::SnaplineColor), true);
							widgets->colorpicker("Head Box", reinterpret_cast<c_vec4*>(Settings::HeadBoxColor), true);
							widgets->colorpicker("Body Dot", reinterpret_cast<c_vec4*>(Settings::BodyDotColor), true);
						}
						widgets->end_child();
					}
					gui->end_group();

					gui->sameline();

					gui->begin_group();
					{
						widgets->child("V", "Info Colors");
						{
							widgets->colorpicker("Distance", reinterpret_cast<c_vec4*>(Settings::DistanceColor), true);
							widgets->colorpicker("HP High", reinterpret_cast<c_vec4*>(Settings::HPHighColor), true);
							widgets->colorpicker("HP Low", reinterpret_cast<c_vec4*>(Settings::HPLowColor), true);
							widgets->colorpicker("Team Color", reinterpret_cast<c_vec4*>(Settings::TeamColor), true);
						}
						widgets->end_child();
					}
					gui->end_group();
				}

				if (var->tab.tab_current == 3)
				{
					gui->begin_group();
					{
						widgets->child("D", "Settings");
						{
							widgets->checkbox("Debug Console");
							widgets->checkbox("Watermark");
							widgets->slider("Interface size");
							widgets->colorpicker("Accent color", &clr->accent.Value, true);
						}
						widgets->end_child();
					}
					gui->end_group();

					gui->sameline();

					gui->begin_group();
					{
						widgets->child("V", "Actions");
						{
							if (widgets->selectable("Save Config", false))
								Menu::SaveConfig();
							if (widgets->selectable("Reset Config", false))
								Menu::ResetConfig();
							if (widgets->selectable("Close Menu", false))
								Menu::Open = false;
						}
						widgets->end_child();
					}
					gui->end_group();
				}

				static float top_shadow_alpha = 0.f;
				gui->easing(top_shadow_alpha, gui->get_window()->Scroll.y > SCALE(1) ? 1.f : 0.f, 12.f, dynamic_easing);	
				draw->rect_filled_multi_color(var->widget.draw_list, gui->get_window()->Rect().Min, gui->get_window()->Rect().GetTR() + SCALE(0, 30 * top_shadow_alpha), draw->get_clr(clr->layout, 1.f * top_shadow_alpha), draw->get_clr(clr->layout, 1.f * top_shadow_alpha), draw->get_clr(clr->layout, 0.f), draw->get_clr(clr->layout, 0.f));
				
				static float bottom_shadow_alpha = 0.f;
				gui->easing(bottom_shadow_alpha, gui->get_window()->Scroll.y < gui->get_window()->ScrollMax.y - SCALE(1) ? 1.f : 0.f, 12.f, dynamic_easing);
				draw->rect_filled_multi_color(var->widget.draw_list, gui->get_window()->Rect().GetBL() - SCALE(0, 30 * bottom_shadow_alpha), gui->get_window()->Rect().Max, draw->get_clr(clr->layout, 0.f), draw->get_clr(clr->layout, 0.f), draw->get_clr(clr->layout, 1.f * bottom_shadow_alpha), draw->get_clr(clr->layout, 1.f * bottom_shadow_alpha));
			}
			gui->end_content();

			gui->pop_var(4);
		}
		gui->end_content();

		widgets->blackout();
	}
	gui->end();

	gui->easing(var->blackout.alpha, var->blackout.active ? 1.f : 0.f, 7.f, static_easing);

	float dpi = cfg->get<slider_t>("Interface size").callback;
	if (gui->mouse_released(0) && round(dpi) != var->gui.stored_dpi)
	{
		var->gui.stored_dpi = round(dpi);
		var->gui.dpi_changed = true;
	}
}