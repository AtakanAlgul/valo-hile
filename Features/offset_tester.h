#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <chrono>
#include "Core/main.h"
#include "Driver/driver.h"
#include "Auth/skStr.h"

namespace OffsetTest {

struct TestItem {
    std::string name;
    uintptr_t offset_val;
    uintptr_t read_address;
    uint64_t result_value;
    std::string status_text;
    bool success;
    bool is_pending;
};

struct DiagnosticReport {
    bool driver_ok = false;
    int pid = 0;
    uintptr_t base_address = 0;
    uintptr_t cr3 = 0;
    uintptr_t uworld = 0;
    std::string uworld_method = "Yok";
    int total_count = 0;
    int pass_count = 0;
    int fail_count = 0;
    int pending_count = 0;
    std::vector<TestItem> items;

    // Feature readiness
    bool esp_box_ready = false;
    bool skeleton_ready = false;
    bool health_ready = false;
    bool aimbot_ready = false;
    bool triggerbot_ready = false;
    bool spike_ready = false;
    bool radar_ready = false;
    bool names_ready = false;
    std::string timestamp;
};

inline DiagnosticReport g_last_report;
inline std::mutex g_report_mutex;

inline std::string FormatHex(uintptr_t val) {
    std::stringstream ss;
    ss << "0x" << std::uppercase << std::hex << val;
    return ss.str();
}

inline void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole && hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, color);
    }
}

// Forward declarations from cheats.h
uintptr_t ResolveValidUWorld(uintptr_t base, std::string& out_method);
extern uint64_t g_NameXorKey;
uint32_t BruteForceFNameKey();
std::string AVERISTY(int key);

inline DiagnosticReport RunDiagnostic() {
    DiagnosticReport rep;

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    struct tm tm_buf;
    localtime_s(&tm_buf, &time_t_now);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", &tm_buf);
    rep.timestamp = time_str;

    // 1. Driver Check
    rep.driver_ok = (driver::driverHandler != INVALID_HANDLE_VALUE && driver::driverHandler != nullptr);
    rep.items.push_back({
        "Driver Baglantisi",
        0,
        0,
        (uint64_t)(rep.driver_ok ? 1 : 0),
        rep.driver_ok ? "[ OK ] Driver Aktif" : "[ FAIL ] Baglanti Yok",
        rep.driver_ok,
        false
    });

    // 2. Process Check
    rep.pid = driver::processid;
    if (rep.pid == 0) {
        rep.pid = driver::find_process(skCrypt(L"VALORANT-Win64-Shipping.exe").decrypt());
        if (rep.pid != 0) driver::processid = rep.pid;
    }
    bool pid_ok = (rep.pid != 0);
    rep.items.push_back({
        "Valorant Process ID",
        0,
        0,
        (uint64_t)rep.pid,
        pid_ok ? ("[ OK ] PID: " + std::to_string(rep.pid)) : "[ FAIL ] Valorant Calismiyor",
        pid_ok,
        false
    });

    // 3. Base Address Check
    rep.base_address = baseee;
    if (rep.base_address == 0 && pid_ok && rep.driver_ok) {
        rep.base_address = driver::FindProcessBaseByPID(rep.pid);
        if (rep.base_address != 0) baseee = rep.base_address;
    }
    bool base_ok = (rep.base_address > 0x10000 && rep.base_address < 0x7FFFFFFFFFFF);
    rep.items.push_back({
        "Process Base Address",
        0,
        rep.base_address,
        (uint64_t)rep.base_address,
        base_ok ? ("[ OK ] " + FormatHex(rep.base_address)) : "[ FAIL ] Modul Bulunamadi",
        base_ok,
        false
    });

    // 4. CR3 Translation Check
    rep.cr3 = driver::process_cr3;
    if (rep.cr3 == 0 && rep.driver_ok && pid_ok) {
        rep.cr3 = driver::SetCr3_Normal();
        if (rep.cr3 != 0) driver::process_cr3 = rep.cr3;
    }
    bool cr3_ok = (rep.cr3 != 0);
    rep.items.push_back({
        "CR3 / DirBase",
        0,
        0,
        (uint64_t)rep.cr3,
        cr3_ok ? ("[ OK ] CR3: " + FormatHex(rep.cr3)) : "[ FAIL ] CR3 Alinamadi",
        cr3_ok,
        false
    });

    if (!base_ok || !rep.driver_ok) {
        for (const auto& it : rep.items) {
            rep.total_count++;
            if (it.success) rep.pass_count++;
            else rep.fail_count++;
        }
        std::lock_guard<std::mutex> lock(g_report_mutex);
        g_last_report = rep;
        return rep;
    }

    // 5. UWorld Resolution
    rep.uworld = ResolveValidUWorld(rep.base_address, rep.uworld_method);
    bool uworld_ok = (rep.uworld > 0x10000 && rep.uworld < 0x7FFFFFFFFFFF);
    rep.items.push_back({
        "UWorld (" + rep.uworld_method + ")",
        offsets::UWorld,
        rep.base_address + offsets::UWorld,
        (uint64_t)rep.uworld,
        uworld_ok ? ("[ OK ] " + FormatHex(rep.uworld)) : "[ FAIL ] UWorld Okunamadi",
        uworld_ok,
        false
    });

    uintptr_t game_inst = 0;
    uintptr_t local_players_arr = 0;
    uintptr_t local_player_ptr = 0;
    uintptr_t player_ctrl = 0;
    uintptr_t my_pawn = 0;
    uintptr_t cam_mgr = 0;
    uintptr_t game_state = 0;
    uintptr_t actor_arr = 0;
    int actor_cnt = 0;
    uintptr_t mesh_ptr = 0;
    uintptr_t bone_arr = 0;
    int bone_cnt = 0;
    uintptr_t dmg_hnd = 0;
    float health_val = 0.f;
    uintptr_t root_cmp = 0;

    if (uworld_ok) {
        // 6. GameInstance
        game_inst = driver::read2<uintptr_t>(rep.uworld + offsets::game_instance);
        bool gi_ok = (game_inst > 0x10000 && game_inst < 0x7FFFFFFFFFFF);
        rep.items.push_back({
            "GameInstance",
            offsets::game_instance,
            rep.uworld + offsets::game_instance,
            (uint64_t)game_inst,
            gi_ok ? ("[ OK ] " + FormatHex(game_inst)) : "[ FAIL ] Gecersiz Pointer",
            gi_ok,
            false
        });

        // 7. LocalPlayers Array
        if (gi_ok) {
            local_players_arr = driver::read2<uintptr_t>(game_inst + offsets::localplayer);
            bool lp_arr_ok = (local_players_arr > 0x10000 && local_players_arr < 0x7FFFFFFFFFFF);
            rep.items.push_back({
                "LocalPlayer Array",
                offsets::localplayer,
                game_inst + offsets::localplayer,
                (uint64_t)local_players_arr,
                lp_arr_ok ? ("[ OK ] " + FormatHex(local_players_arr)) : "[ FAIL ] Gecersiz Array",
                lp_arr_ok,
                false
            });

            // 8. LocalPlayer Pointer
            if (lp_arr_ok) {
                local_player_ptr = driver::read2<uintptr_t>(local_players_arr);
                bool lp_ok = (local_player_ptr > 0x10000 && local_player_ptr < 0x7FFFFFFFFFFF);
                rep.items.push_back({
                    "LocalPlayer",
                    0,
                    local_players_arr,
                    (uint64_t)local_player_ptr,
                    lp_ok ? ("[ OK ] " + FormatHex(local_player_ptr)) : "[ FAIL ] Gecersiz Pointer",
                    lp_ok,
                    false
                });

                // 9. PlayerController
                if (lp_ok) {
                    player_ctrl = driver::read2<uintptr_t>(local_player_ptr + offsets::player_controller);
                    bool pc_ok = (player_ctrl > 0x10000 && player_ctrl < 0x7FFFFFFFFFFF);
                    rep.items.push_back({
                        "PlayerController",
                        offsets::player_controller,
                        local_player_ptr + offsets::player_controller,
                        (uint64_t)player_ctrl,
                        pc_ok ? ("[ OK ] " + FormatHex(player_ctrl)) : "[ FAIL ] Gecersiz Controller",
                        pc_ok,
                        false
                    });

                    // 10. LocalPawn (APawn)
                    if (pc_ok) {
                        my_pawn = driver::read2<uintptr_t>(player_ctrl + offsets::apawn);
                        bool pawn_ok = (my_pawn > 0x10000 && my_pawn < 0x7FFFFFFFFFFF);
                        rep.items.push_back({
                            "LocalPawn (APawn)",
                            offsets::apawn,
                            player_ctrl + offsets::apawn,
                            (uint64_t)my_pawn,
                            pawn_ok ? ("[ OK ] " + FormatHex(my_pawn)) : "[ PENDING ] Lobide / Henuz Dogmadi",
                            pawn_ok,
                            !pawn_ok // pending if in lobby
                        });

                        // 11. CameraManager
                        cam_mgr = driver::read2<uintptr_t>(player_ctrl + offsets::camera_manager);
                        bool cam_ok = (cam_mgr > 0x10000 && cam_mgr < 0x7FFFFFFFFFFF);
                        rep.items.push_back({
                            "CameraManager",
                            offsets::camera_manager,
                            player_ctrl + offsets::camera_manager,
                            (uint64_t)cam_mgr,
                            cam_ok ? ("[ OK ] " + FormatHex(cam_mgr)) : "[ FAIL ] Kamera Yoneticisi Yok",
                            cam_ok,
                            false
                        });

                        // 12. Camera ViewInfo
                        if (cam_ok) {
                            char buf[0x34] = { 0 };
                            driver::readvm((PVOID)(cam_mgr + offsets::ViewInfo), buf, 0x34);
                            float fov = *(float*)(buf + 0x30);
                            bool fov_ok = (fov >= 40.0f && fov <= 135.0f);
                            rep.items.push_back({
                                "Camera ViewInfo (FOV)",
                                offsets::ViewInfo,
                                cam_mgr + offsets::ViewInfo,
                                (uint64_t)(fov * 100),
                                fov_ok ? ("[ OK ] FOV: " + std::to_string((int)fov)) : "[ FAIL ] Gecersiz FOV",
                                fov_ok,
                                false
                            });
                        }
                    }
                }
            }
        }

        // 13. GameState
        game_state = driver::read2<uintptr_t>(rep.uworld + offsets::Game_state);
        bool gs_ok = (game_state > 0x10000 && game_state < 0x7FFFFFFFFFFF);
        rep.items.push_back({
            "GameState",
            offsets::Game_state,
            rep.uworld + offsets::Game_state,
            (uint64_t)game_state,
            gs_ok ? ("[ OK ] " + FormatHex(game_state)) : "[ FAIL ] GameState Okunamadi",
            gs_ok,
            false
        });

        // 14. ActorArray & ActorCount
        if (gs_ok) {
            actor_arr = driver::read2<uintptr_t>(game_state + offsets::actor_array);
            actor_cnt = driver::read2<INT32>(game_state + offsets::actors_count);
            bool act_ok = (actor_arr > 0x10000 && actor_arr < 0x7FFFFFFFFFFF && actor_cnt > 0 && actor_cnt < 3000);
            rep.items.push_back({
                "ActorArray & Count",
                offsets::actor_array,
                game_state + offsets::actor_array,
                (uint64_t)actor_cnt,
                act_ok ? ("[ OK ] " + std::to_string(actor_cnt) + " Aktor") : "[ FAIL ] Aktor Listesi Bos",
                act_ok,
                false
            });

            // Find a candidate player pawn to test mesh and bones
            uintptr_t test_pawn = my_pawn;
            if (test_pawn == 0 && act_ok) {
                for (int i = 0; i < (std::min)(actor_cnt, 150); i++) {
                    uintptr_t act = driver::read2<uintptr_t>(actor_arr + (i * offsets::actor_count));
                    if (!driver::is_valid(act)) continue;
                    uintptr_t m = driver::read2<uintptr_t>(act + offsets::mesh);
                    if (driver::is_valid(m)) {
                        int bc = driver::read2<INT32>(m + offsets::bone_count);
                        if (bc >= 90 && bc <= 115) {
                            test_pawn = act;
                            break;
                        }
                    }
                }
            }

            // 15. Mesh Component
            if (test_pawn != 0) {
                mesh_ptr = driver::read2<uintptr_t>(test_pawn + offsets::mesh);
                bool mesh_ok = driver::is_valid(mesh_ptr);
                rep.items.push_back({
                    "USkeletalMeshComponent",
                    offsets::mesh,
                    test_pawn + offsets::mesh,
                    (uint64_t)mesh_ptr,
                    mesh_ok ? ("[ OK ] " + FormatHex(mesh_ptr)) : "[ FAIL ] Mesh Yok",
                    mesh_ok,
                    false
                });

                // 16. BoneArray & BoneCount
                if (mesh_ok) {
                    bone_arr = driver::read2<uintptr_t>(mesh_ptr + offsets::bone_array);
                    bone_cnt = driver::read2<INT32>(mesh_ptr + offsets::bone_count);
                    bool bone_ok = (driver::is_valid(bone_arr) && bone_cnt >= 90 && bone_cnt <= 120);
                    rep.items.push_back({
                        "BoneArray (Kemikler)",
                        offsets::bone_array,
                        mesh_ptr + offsets::bone_array,
                        (uint64_t)bone_cnt,
                        bone_ok ? ("[ OK ] " + std::to_string(bone_cnt) + " Kemik") : "[ FAIL ] Gecersiz Kemik Sayisi",
                        bone_ok,
                        false
                    });
                }

                // 17. DamageHandler & Health
                dmg_hnd = driver::read2<uintptr_t>(test_pawn + offsets::damage_handler);
                if (dmg_hnd > 0x10000 && dmg_hnd < 0x7FFFFFFFFFFF) {
                    health_val = driver::read2<float>(dmg_hnd + offsets::health);
                    bool hp_ok = (health_val > 0.f && health_val <= 300.f);
                    rep.items.push_back({
                        "DamageHandler & Can",
                        offsets::damage_handler,
                        dmg_hnd + offsets::health,
                        (uint64_t)(health_val * 10),
                        hp_ok ? ("[ OK ] Can: " + std::to_string((int)health_val)) : "[ FAIL ] Can Okunamadi",
                        hp_ok,
                        false
                    });
                } else {
                    rep.items.push_back({
                        "DamageHandler",
                        offsets::damage_handler,
                        test_pawn + offsets::damage_handler,
                        0,
                        "[ FAIL ] DamageHandler Yok",
                        false,
                        false
                    });
                }

                // 18. RootComponent
                root_cmp = driver::read2<uintptr_t>(test_pawn + offsets::root_component);
                bool rc_ok = (root_cmp > 0x10000 && root_cmp < 0x7FFFFFFFFFFF);
                rep.items.push_back({
                    "RootComponent",
                    offsets::root_component,
                    test_pawn + offsets::root_component,
                    (uint64_t)root_cmp,
                    rc_ok ? ("[ OK ] " + FormatHex(root_cmp)) : "[ FAIL ] RootComponent Yok",
                    rc_ok,
                    false
                });
            } else {
                rep.items.push_back({
                    "Oyuncu / Bot Mesh",
                    offsets::mesh,
                    0,
                    0,
                    "[ PENDING ] Lobide / Haritaya girince test edilecek",
                    false,
                    true
                });
            }
        }
    }

    // 19. FNamePool Check
    uintptr_t fname_chunk = driver::read2<uintptr_t>(rep.base_address + offsets::FnamePool + 16);
    bool fname_ok = (fname_chunk > 0x10000 || g_NameXorKey != 0);
    rep.items.push_back({
        "FNamePool (Isim Cozucu)",
        offsets::FnamePool,
        rep.base_address + offsets::FnamePool,
        (uint64_t)fname_chunk,
        fname_ok ? ("[ OK ] " + FormatHex(fname_chunk)) : "[ FAIL ] FNamePool Okunamadi",
        fname_ok,
        false
    });

    // Feature Readiness Calculation
    rep.esp_box_ready = (base_ok && uworld_ok && (mesh_ptr != 0 || my_pawn != 0));
    rep.skeleton_ready = (mesh_ptr != 0 && bone_arr != 0 && bone_cnt >= 90);
    rep.health_ready = (dmg_hnd != 0 && health_val > 0.f);
    rep.aimbot_ready = (cam_mgr != 0 && (mesh_ptr != 0 || my_pawn != 0));
    rep.triggerbot_ready = (cam_mgr != 0 && (mesh_ptr != 0 || my_pawn != 0));
    rep.spike_ready = (actor_arr != 0 && actor_cnt > 0);
    rep.radar_ready = (uworld_ok && cam_mgr != 0);
    rep.names_ready = fname_ok;

    // Count totals
    for (const auto& item : rep.items) {
        rep.total_count++;
        if (item.success) rep.pass_count++;
        else if (item.is_pending) rep.pending_count++;
        else rep.fail_count++;
    }

    {
        std::lock_guard<std::mutex> lock(g_report_mutex);
        g_last_report = rep;
    }
    return rep;
}

inline void PrintReportToConsole(const DiagnosticReport& rep) {
    SetConsoleColor(11); // Cyan
    std::cout << "\n=================================================================\n";
    std::cout << "                 AVERIS OFFSET OKUMA VE DIAGNOSTIK TESTI         \n";
    std::cout << "=================================================================\n";
    SetConsoleColor(7); // White

    std::cout << "[*] Zaman: " << rep.timestamp << "\n";
    std::cout << "[*] Valorant PID : " << rep.pid << "\n";
    std::cout << "[*] Base Adresi  : " << FormatHex(rep.base_address) << "\n";
    std::cout << "[*] UWorld Modu  : " << rep.uworld_method << "\n\n";

    std::cout << std::left << std::setw(28) << "OFFSET / BILESEN"
              << std::setw(14) << "OFFSET DEGERI"
              << std::setw(18) << "ADRES / DEGER"
              << "DURUM\n";
    std::cout << "-----------------------------------------------------------------\n";

    for (const auto& item : rep.items) {
        std::cout << std::left << std::setw(28) << item.name
                  << std::setw(14) << (item.offset_val ? FormatHex(item.offset_val) : "-")
                  << std::setw(18) << (item.result_value ? FormatHex((uintptr_t)item.result_value) : "-");

        if (item.success) {
            SetConsoleColor(10); // Green
            std::cout << item.status_text << "\n";
        } else if (item.is_pending) {
            SetConsoleColor(14); // Yellow
            std::cout << item.status_text << "\n";
        } else {
            SetConsoleColor(12); // Red
            std::cout << item.status_text << "\n";
        }
        SetConsoleColor(7);
    }

    std::cout << "-----------------------------------------------------------------\n";
    SetConsoleColor(11);
    std::cout << ">> OZELLIK HAZIRLIK DURUMU:\n";
    SetConsoleColor(7);

    auto print_feat = [](const char* name, bool ok) {
        std::cout << "  * " << std::left << std::setw(24) << name << " : ";
        if (ok) {
            SetConsoleColor(10);
            std::cout << "[ HAZIR / CALISIYOR ]\n";
        } else {
            SetConsoleColor(14);
            std::cout << "[ BEKLEMEDE / OYUNA GIRIN ]\n";
        }
        SetConsoleColor(7);
    };

    print_feat("Kutu / Box ESP", rep.esp_box_ready);
    print_feat("Iskelet / Skeleton", rep.skeleton_ready);
    print_feat("Can Bari / Health", rep.health_ready);
    print_feat("Aimbot Hedefleme", rep.aimbot_ready);
    print_feat("Triggerbot", rep.triggerbot_ready);
    print_feat("Spike Timer & ESP", rep.spike_ready);
    print_feat("Harita / Mini Radar", rep.radar_ready);
    print_feat("Ajan / Silah Isimleri", rep.names_ready);

    std::cout << "=================================================================\n";
    if (rep.fail_count == 0) {
        SetConsoleColor(10);
        std::cout << "[+] TEST BASARILI: Tum kritik offsetler basariyla dogrulandi!\n";
    } else {
        SetConsoleColor(14);
        std::cout << "[!] BILGI: " << rep.pass_count << " Basarili, "
                  << rep.fail_count << " Hata, "
                  << rep.pending_count << " Beklemede (Oyuna girince aktiflesir)\n";
    }
    SetConsoleColor(7);
    std::cout << "=================================================================\n\n";
}

} // namespace OffsetTest
