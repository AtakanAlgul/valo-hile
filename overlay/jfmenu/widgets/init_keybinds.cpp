#include "../headers/includes.h"

void c_widgets::init_keybinds()
{
	for (auto widget : cfg->order)
	{
		if (widget.second == checkbox_type)
		{
			checkbox_t* data = cfg->fill<checkbox_t>(widget.first);

			if (data->keybinds_enabled || data->is_weapon)
			{
				for (auto& kb : data->keybinds_list)
				{
					if (kb.mode == 0)
					{
						if (ImGui::IsKeyPressed((ImGuiKey)kb.key, false))
						{
							data->enabled = !data->enabled;
                            data->last_keybind = kb;
						}
					}

					if (kb.mode == 1)
					{
						if (ImGui::IsKeyDown((ImGuiKey)kb.key))
						{
							data->enabled = true;
                            data->last_keybind = kb;
						}
						if (ImGui::IsKeyReleased((ImGuiKey)kb.key))
						{
							data->enabled = false;
                            data->last_keybind = kb;
						}
					}
				}
			}
		}
	}
}