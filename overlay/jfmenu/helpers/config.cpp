#include "../headers/config.h"

void c_config::init_config()
{
    static bool init = false;

    if (!init)
    {
        // Aimbot options
        add_option<checkbox_t>("Enable Aimbot", true, true);
        add_option<checkbox_t>("Draw FOV", true);
        add_option<checkbox_t>("Filled FOV", false);
        add_option<checkbox_t>("Visibility Check", true);
        add_option<checkbox_t>("Recoil Control", true);
        add_option<slider_t>("RCS Strength", 0.6f, 0.0f, 1.0f, "%.2f");
        add_option<checkbox_t>("Triggerbot", false, true);
        add_option<slider_t>("Trigger Delay", 90.f, 0.f, 500.f, "%.0f ms");
        add_option<dropdown_t>("Target Bone", 0, std::vector<std::string>{ "Head", "Neck", "Chest" });
        add_option<slider_t>("FOV", 40.f, 1.f, 150.f, "%.0f");
        add_option<slider_t>("Smooth", 10.f, 1.f, 30.f, "%.1f");

        // Visuals (ESP) options
        add_option<checkbox_t>("Box ESP", true);
        add_option<checkbox_t>("Corner Box", true);
        add_option<checkbox_t>("3D Box", false);
        add_option<checkbox_t>("Skeleton", true);
        add_option<checkbox_t>("Head Box", false);
        add_option<checkbox_t>("Health Bar", true);
        add_option<checkbox_t>("Snaplines", false);
        add_option<checkbox_t>("Distance", true);
        add_option<checkbox_t>("Team Check", true);
        add_option<checkbox_t>("Visible Check", false);
        add_option<checkbox_t>("Ignore Dormant", true);
        add_option<checkbox_t>("Body Dot", false);
        add_option<checkbox_t>("Memory Radar", false);
        add_option<checkbox_t>("Spike Timer", false);
        add_option<checkbox_t>("View Angle", false);
        add_option<checkbox_t>("Agent Icons", false);
        add_option<checkbox_t>("Rainbow Skeleton", false);
        add_option<slider_t>("ESP Thickness", 1.0f, 0.5f, 5.0f, "%.1f px");
        add_option<checkbox_t>("Legit ESP", false, true);
        add_option<dropdown_t>("Legit Mode", 0, std::vector<std::string>{ "On Toggle (Hold)", "On Time" });
        add_option<slider_t>("Legit Time", 10.f, 1.f, 50.f, "%.fs");
        add_option<checkbox_t>("Debug Console", false);
        add_option<checkbox_t>("Watermark", false);
        add_option<slider_t>("Interface size", 100.f, 100.f, 200.f, "%.f%%");
        
        //weapons

        add_option<checkbox_t>("ak47_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("thompson_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("m249_lmg_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("l96_rifle_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("semi_automatic_rifle_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("thompson_custom_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("bolt_action_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("spas_12_weapon", false, true, std::vector<keybind_t>{ }, true);
        add_option<checkbox_t>("mp5_weapon", false, true, std::vector<keybind_t>{ }, true);

        init = true;
    }
}
