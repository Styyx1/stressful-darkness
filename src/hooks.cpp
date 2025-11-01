#include "hooks.h"
#include "settings.h"
#include "utility.h"

namespace Hooks
{
    Timer myTimer;

    void MainUpdate::PlayerUpdate(RE::PlayerCharacter *player, float a_delta)
    {
        auto cell = ActorUtil::GetPlayerCell(player);

        bool in_dungeon = cell && CellUtil::IsDungeon(cell) && isInside(player);

        if (!in_dungeon) {
            if (inside) {
                inside = false;
                RE::ImageSpaceModifierInstanceForm::Stop(Options::Forms::imod);
                myTimer.Reset();
            }
            frameCount++;
            _Hook0(player, a_delta);
            return;
        }

        if (!inside) {
            inside = true;
        }

        if (++frameCount > 10) {
            frameCount = 0;
            ChangeImod(player);
        }        

        if (ShouldIncreaseStress(player)) {
            if (!myTimer.IsRunning())
                myTimer.Start();

            if (myTimer.ElapsedSeconds() >= Options::Settings::stress_increase_seconds.GetValue()) {
                AddStress(Options::Forms::stress_global);
                myTimer.Reset();
            }
        }
        else {
            myTimer.Reset();
        }

        _Hook0(player, a_delta);
    }

    void MainUpdate::AddStress(RE::TESGlobal *a_stress)
    {
        if(!CanAddStress())
			return;
        a_stress->value += Utility::StressGain();
        RE::DebugNotification(Options::Settings::stress_message.GetValue().c_str(), nullptr, true);
        if (GetCurrentStress() > 100.f)
            a_stress->value = 100.f;        
    }

    void MainUpdate::ChangeImod(RE::PlayerCharacter *player)
    {
        if (Options::Forms::imod != nullptr && Options::Settings::allow_darkness_change.GetValue())
        {
            float max_range = 0.98;
            float min_range = 0.0;
            float str_imod = std::min(std::max((Options::Forms::stress_global->value / 100), min_range), max_range);

            RE::ImageSpaceModifierInstanceForm::Stop(Options::Forms::imod);
            RE::ImageSpaceModifierInstanceForm::Trigger(Options::Forms::imod, str_imod, player->As<RE::NiAVObject>());
        }
        return;
    }
    bool MainUpdate::isInside(RE::PlayerCharacter *player)
    {
        bool isInside = false;
        auto cell = ActorUtil::GetPlayerCell(player);        
        if (cell && cell->IsInteriorCell()) {
            isInside = true;
        }
        else {
            isInside = false;
        }
        return isInside;
    }
    bool MainUpdate::CanAddStress()
    {
        return Options::Forms::stress_enabled_global->value != 0;
    }
    float MainUpdate::GetCurrentStress()
    {
        return Options::Forms::stress_global->value;
    }
    bool MainUpdate::ShouldIncreaseStress(RE::PlayerCharacter* player)
    {
        auto process = player->GetHighProcess();
        bool is_dark_here = process && process->lightLevel < Options::Settings::light_level_limit.GetValue();
        bool is_not_monster = !Utility::IsSuperNatural(player);
        bool has_night_eye_effect = ActorUtil::ActorHasEffectOfTypeActive(player, RE::EffectArchetypes::ArchetypeID::kNightEye);
        bool night_eye_protects = Options::Settings::night_eye_no_stress.GetValue();
        bool should_increase_stress = is_dark_here && is_not_monster && (!night_eye_protects || !has_night_eye_effect);

        return should_increase_stress;
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

    double Timer::ElapsedSeconds() const
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
    void HideNPCsInDark::ActorUpdate(RE::Character* a_actor, float a_delta)
    {
        int32_t stress_hide_npcs = Options::Settings::npc_hide_threshold.GetValue();
        if (MainUpdate::GetCurrentStress() < static_cast<float>(stress_hide_npcs)) {
            if (a_actor->GetAlpha() < 1.0) {
                a_actor->SetAlpha();
            }            
            _Hook1(a_actor, a_delta);
            return;
		}

        RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
        float distance_full_fade = Options::Settings::npc_hide_distance_full_fade.GetValue();
        float distance_no_fade = Options::Settings::npc_hide_distance_no_fade.GetValue();
        float light_level_threshold = Options::Settings::npc_hide_light_level_threshold.GetValue();
        float fade_range = distance_full_fade - distance_no_fade;
        float minAlpha = 0.05f;

        if (float distance = a_actor->GetDistance(player); distance >= distance_full_fade && a_actor->GetHighProcess() && a_actor->GetHighProcess()->lightLevel <= light_level_threshold)
        {
            float fade_progress = std::min(std::max((distance - distance_no_fade) / fade_range, 0.0f), 1.0f);
            float alpha = std::lerp(1.0f, minAlpha, fade_progress);
            a_actor->SetAlpha(alpha);
        }
        else {
            if (a_actor->GetAlpha() < 1.0) {
                a_actor->SetAlpha();
            }
        }
		_Hook1(a_actor, a_delta);
    }
}
