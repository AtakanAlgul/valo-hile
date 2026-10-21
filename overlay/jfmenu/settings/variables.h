#pragma once
#include <string>
#include <vector>
#include "imgui.h"
#include "../headers/flags.h"
#include <d3d11.h>
#include <windows.h>

struct subtab_t {
	std::string name{};
	std::vector<std::string> weapons_list{};
};

struct tab_t {
	std::string icon{};
	std::string name{};
	std::vector<subtab_t> subtabs_list{};
};

class c_variables
{
public:

	struct
	{
		float dpi = 1.0f;
		int stored_dpi = 100;
		bool dpi_changed = true;
	} gui;

	struct 
	{
		std::vector<tab_t> list = {
			tab_t{ "K", "Aimbot" },
			tab_t{ "B", "Visuals", std::vector<subtab_t>{
					subtab_t{ "Players" },
					subtab_t{ "World & Radar" },
					subtab_t{ "Legit" }
				}
			},
			tab_t{ "A", "Colors" },
			tab_t{ "C", "Misc" }
		};

		int tab_current = 0;
		int tab_stored = 0;

		int subtab_current = 0;
		int subtab_stored = 0;

		int item_current = 0;
		int item_stored = 0;

		float alpha = 0.f;

		ImDrawList* draw_list;

	} tab;

	struct {
		ImDrawList* draw_list;
	} widget;

	struct 
	{
		float alpha;
		bool active;
	} blackout;

	struct 
	{
		ImTextureID background;
		ImTextureID user_logo;
		ImTextureID logo;
		ImTextureID ak47_weapon;
		ImTextureID thompson_weapon;
		ImTextureID m249_lmg_weapon;
		ImTextureID l96_rifle_weapon;
		ImTextureID semi_automatic_rifle_weapon;
		ImTextureID thompson_custom_weapon;
		ImTextureID bolt_action_weapon;
		ImTextureID spas_12_weapon;
		ImTextureID mp5_weapon;
	} img;

	struct 
	{
		ID3D11Device* device;
		ID3D11DeviceContext* ctx;
		IDXGISwapChain* swap_chain;
	} dx;

	struct
	{
		HWND hwnd;
		RECT rc;
	} winapi;

	gui_style style;

};

inline std::unique_ptr<c_variables> var = std::make_unique<c_variables>();
