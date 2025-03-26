#include "hooks.h"
#include "settings.h"
#include "utility.h"

namespace Hooks
{
    void InstallHooks()
    {
        logs::info("***************HOOKS***************");
        MainUpdate::InstallUpdate();
    }

    Timer myTimer;

    void MainUpdate::PlayerUpdate(RE::PlayerCharacter *player, float a_delta)
    {

        auto a_cell = player->GetParentCell();

        if (a_cell && Utility::IsDungeon(a_cell))
        {
            if (frameCount > 10)
            {
                frameCount = 0;
                ChangeImod(player);
            }
            if (player->GetHighProcess()->lightLevel < Options::Values::light_level_limit.GetValue() && !Utility::IsSuperNatural(player))
            {

                if (!myTimer.IsRunning())
                {
                    myTimer.Start();
                }

                if (myTimer.ElapsedSeconds() >= Options::Values::stress_increase_seconds.GetValue())
                {
                    AddStress(Options::Forms::stress_global);
                    myTimer.Reset(); // Reset or Stop if needed
                }
            }
            else
            {
                myTimer.Reset();
            }
        }

        frameCount++;

        v_func(player, a_delta);
    }

    void MainUpdate::InstallUpdate()
    {
        REL::Relocation<std::uintptr_t> PlayerVTBL{RE::VTABLE_PlayerCharacter[0]};
        v_func = PlayerVTBL.write_vfunc(0xAD, PlayerUpdate);
        logs::info("Hook:Player Update");
    }

    void MainUpdate::AddStress(RE::TESGlobal *a_stress)
    {
        a_stress->value += Utility::StressGain();
        RE::DebugNotification(Options::Values::stress_message.GetValue().c_str(), nullptr, true);
        if (a_stress->value > 100)
        {
            a_stress->value = 100;
        }
    }

    void MainUpdate::ChangeImod(RE::PlayerCharacter *player)
    {
        if (Options::Forms::imod != nullptr && Options::Values::allow_darkness_change.GetValue())
        {
            float max_range = 0.98;
            float min_range = 0.0;
            float str_imod = std::min(std::max((Options::Forms::stress_global->value / 100), min_range), max_range);

            RE::ImageSpaceModifierInstanceForm::Stop(Options::Forms::imod);
            RE::ImageSpaceModifierInstanceForm::Trigger(Options::Forms::imod, str_imod, player->As<RE::NiAVObject>());
        }
        return;
    }
    void Timer::Start()
    {
        if (!running)
        {
            startTime = std::chrono::steady_clock::now();
            running = true;
        }
    }

    void Timer::Stop()
    {
        running = false;
    }

    void Timer::Reset()
    {
        running = false;
    }

    double Timer::ElapsedSeconds()
    {
        if (!running)
            return 0.0; // If stopped, return 0
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - startTime).count();
    }

    bool Timer::IsRunning() const
    {
        return running;
    }
}
