#include "hooks.h"
#include "settings.h"
#include "utility.h"
#include "imod.h"


namespace Hooks
{
    void InstallHooks()
    {
        MainUpdate::InstallUpdate();
    }

    void MainUpdate::PlayerUpdate(RE::PlayerCharacter* p, float a_delta)
    {
        RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
        // runs every 60 frames by default
        if(frameCount > Settings::frame_count) {            
            frameCount = 0;
            auto a_cell = player->GetParentCell();
            if (a_cell && Utility::IsDungeon(a_cell) && player->GetHighProcess()->lightLevel < Settings::light_level_limit && !Utility::IsSuperNatural(player)) {
                lightLevelCount++;
                logs::debug("counting light level ticks, it is: {}", lightLevelCount);
                if (lightLevelCount >= Settings::light_threshold) {
                    logs::debug("light level is below threshold and the light level count is {}", lightLevelCount);
                    AddStress(Settings::stress_global);
                    lightLevelCount = 0;                                      
                }
            }
            else {
                lightLevelCount = 0;
            }            
        }
        //runs every 30 frames by default and only when in an interior defined as dungeon
        if(frameCount == Settings::frame_count / 2.0f || frameCount == Settings::frame_count) {
            auto a_cell = player->GetParentCell();
            if (a_cell && Utility::IsDungeon(a_cell) && !Utility::IsBeastForm() && !Utility::IsSuperNatural(player)) {
                ChangeImod(player);
            }
        }
        frameCount++;
        v_func(p, a_delta);
    }

    void MainUpdate::InstallUpdate()
    {
        REL::Relocation<std::uintptr_t> PlayerVTBL{ RE::VTABLE_PlayerCharacter[0] };
        v_func = PlayerVTBL.write_vfunc(0xAD, PlayerUpdate);
        logs::info("hook:Player Update");
    }

    void MainUpdate::AddStress(RE::TESGlobal* a_stress)
    {
        a_stress->value += Utility::StressGain();
        RE::DebugNotification(Settings::stress_message.c_str(), nullptr, true);
        if (a_stress->value > 100) {
            a_stress->value = 100;
        }
    }

    void MainUpdate::ChangeImod(RE::PlayerCharacter* player)
    {
        if (Settings::imod != nullptr && Settings::allow_darkness_change) {            
            float max_range = 1.0;
            float min_range = 0.0;         
            float str_imod = std::min(std::max((Settings::stress_global->value / 100), min_range), max_range); 
            // IMOD strengh is dynamically based on the stress level. by default checks every 30 frames
            logs::debug("str_imod is {}", str_imod);
            RE::ImageSpaceModifierInstanceForm::Stop(Settings::imod);
            RE::ImageSpaceModifierInstanceForm::Trigger(Settings::imod, str_imod, player->As<RE::NiAVObject>());            
        }
        return;

    }
}

