#include "ui.h"

namespace UI {
	void Register() {
        if (!SKSEMenuFramework::IsInstalled()) {
            return;
        }
        SKSEMenuFramework::SetSection(MainMenuStrings::MainTitle);
        SKSEMenuFramework::AddSectionItem(MainMenuStrings::Settings, SetMenu::RenderSettings);
        SKSEMenuFramework::AddSectionItem(MainMenuStrings::Toggles, ToggleMenu::RenderToggles);
        RestoreSettingsFromConfig(true, true);
	}

    void RestoreSettingsFromConfig(bool a_settings, bool a_toggles)
    {
        if (a_settings) {
			SetMenu::stress_increase_temp = Options::Settings::increase_amount.GetValue();
			SetMenu::light_level_limit_temp = Options::Settings::light_level_limit.GetValue();
			SetMenu::stress_time_temp = Options::Settings::stress_increase_seconds.GetValue();
			SetMenu::stress_message_temp = Options::Settings::stress_message.GetValue();
			SetMenu::npc_hide_stress_threshold_temp = Options::Settings::npc_hide_threshold.GetValue();
			SetMenu::npc_hide_full_fade_distance_temp = Options::Settings::npc_hide_distance_full_fade.GetValue();
            SetMenu::npc_hide_no_fade_distance_temp = Options::Settings::npc_hide_distance_no_fade.GetValue();
            SetMenu::npc_hide_light_level_threshold_temp = Options::Settings::npc_hide_light_level_threshold.GetValue();
        }
        if (a_toggles) {
            ToggleMenu::darkness_change_temp = Options::Settings::allow_darkness_change.GetValue();
            ToggleMenu::no_vamp_were_temp = Options::Settings::do_not_affect_supernatural.GetValue();
            ToggleMenu::sneak_levels_temp = Options::Settings::sneak_level_enable.GetValue();
            ToggleMenu::night_eye_immunity_temp = Options::Settings::night_eye_no_stress.GetValue();    
			ToggleMenu::hide_npcs_in_dark_temp = Options::Settings::hide_npcs_in_dark.GetValue();
        }
    }

    void RestoreDefaultSettings(bool a_settings, bool a_toggles)
    {
        using set = Options::Settings;
        using namespace SetMenu;
        using namespace ToggleMenu;
        if (a_settings) {
            stress_increase_temp = 20.0f;
			set::increase_amount.SetValue(stress_increase_temp);
			light_level_limit_temp = 80.0f;
			set::light_level_limit.SetValue(light_level_limit_temp);
			stress_time_temp = 30.0f;
			set::stress_increase_seconds.SetValue(stress_time_temp);
			stress_message_temp = "The darkness here is overwhelming...";
			set::stress_message.SetValue(stress_message_temp);
            npc_hide_full_fade_distance_temp = 2400.0f;
            set::npc_hide_distance_full_fade.SetValue(npc_hide_full_fade_distance_temp);
            npc_hide_stress_threshold_temp = 50;
            set::npc_hide_threshold.SetValue(npc_hide_stress_threshold_temp);
            npc_hide_no_fade_distance_temp = 1200.0f;
            set::npc_hide_distance_no_fade.SetValue(npc_hide_no_fade_distance_temp);
            npc_hide_light_level_threshold_temp = 50.0f;
            set::npc_hide_light_level_threshold.SetValue(npc_hide_light_level_threshold_temp);
        }
        if(a_toggles) {
            darkness_change_temp = true;
            set::allow_darkness_change.SetValue(darkness_change_temp);
            no_vamp_were_temp = false;
            set::do_not_affect_supernatural.SetValue(no_vamp_were_temp);
            sneak_levels_temp = false;
            set::sneak_level_enable.SetValue(sneak_levels_temp);
            night_eye_immunity_temp = false;
            set::night_eye_no_stress.SetValue(night_eye_immunity_temp);
			hide_npcs_in_dark_temp = true;
			set::hide_npcs_in_dark.SetValue(hide_npcs_in_dark_temp);
		}
    }

    void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::BeginItemTooltip()) {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    namespace SetMenu {
        void __stdcall RenderSettings()
        {
			// Light Level Threshold
            FontAwesome::PushSolid();
            ImGui::NewLine();
            ImGui::Text(MainMenuStrings::Settings.c_str());
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::LightLevelThreshold.c_str(), &light_level_limit_temp, 20.0, 150.0, "%.1f")) {
                Options::Settings::light_level_limit.SetValue(light_level_limit_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::LightLevelThreshold.c_str());
            ImGui::SameLine();
            ImGui::Button(MainMenuStrings::LightLevelTitle.c_str());
            ImGui::SameLine();
            ImGui::Text("%.1f", ActorUtil::GetCurrentLightLevelPlayer());

			// Stress Increase
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::StressIncreaseValue.c_str(), &stress_increase_temp, 5.0, 50.0, "%.0f")) {
                Options::Settings::increase_amount.SetValue(stress_increase_temp);
            }
            ImGui::SameLine();
			HelpMarker(Tooltip::StressIncreaseValue.c_str());

            // Stress Time
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::StressTime.c_str(), &stress_time_temp, 20.0, 600.0, "%.2f")) {
                Options::Settings::stress_increase_seconds.SetValue(stress_time_temp);
            }
			ImGui::SameLine();
			HelpMarker(Tooltip::StressTime.c_str());   

            ImGui::NewLine();
            ImGui::Text(MainMenuStrings::HideNPCTitle.c_str());

			//Hide NPCs in Dark stress threshold
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderInt(Button::HideNPCsInDarkStress.c_str(), &npc_hide_stress_threshold_temp, 0, 80)) {
                Options::Settings::npc_hide_threshold.SetValue(static_cast<int>(npc_hide_stress_threshold_temp));
            }
			ImGui::SameLine();
			HelpMarker(Tooltip::HideNPCsInDark.c_str());

            //Hide NPCs Light Threshold

            ImGui::SameLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::NPCHideThreshold.c_str(), &npc_hide_light_level_threshold_temp, 5.0f, 150.0f)) {
                Options::Settings::npc_hide_light_level_threshold.SetValue(npc_hide_light_level_threshold_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::NPCHideThreshold.c_str());

            // Hide NPCs max distance
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::HideFullFadeDistance.c_str(), &npc_hide_full_fade_distance_temp, npc_hide_no_fade_distance_temp + 1.0f, 4000.0f)) {
                Options::Settings::npc_hide_distance_full_fade.SetValue(npc_hide_full_fade_distance_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::HideFullFadeDistance.c_str());

            //Hide NPCs Min Distance

            ImGui::SameLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::HideNoFadeDistance.c_str(), &npc_hide_no_fade_distance_temp, 600.0f, npc_hide_full_fade_distance_temp - 1.0f)) {
                Options::Settings::npc_hide_distance_no_fade.SetValue(npc_hide_no_fade_distance_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::HideNoFadeDistance.c_str());

            

			//Stress Message
			ImGui::NewLine();
			ImGui::SetNextItemWidth(400.0f);
			char buffer[256];
			std::strncpy(buffer, SetMenu::stress_message_temp.c_str(), sizeof(buffer));
			if (ImGui::InputText(Button::StressMessage.c_str(), buffer, sizeof(buffer))) {
				SetMenu::stress_message_temp = std::string(buffer);
				Options::Settings::stress_message.SetValue(SetMenu::stress_message_temp);
			}
			ImGui::SameLine();
			HelpMarker(Tooltip::StressMessage.c_str());


            //Save Config and Default Settings
            ImGui::NewLine();
            ImGui::Text(MainMenuStrings::System.c_str());
            if (ImGui::Button(MainMenuStrings::Save.c_str())) {
                Options::Settings::GetSingleton()->Update(true);
            }
            ImGui::SameLine();
            if (ImGui::Button(MainMenuStrings::Restore.c_str())) {
                RestoreDefaultSettings(true, false);
            }
            FontAwesome::Pop();

        }
    }
    namespace ToggleMenu
    {
        void __stdcall RenderToggles()
        {
            // Allow Darkness Change
            FontAwesome::PushSolid();
            ImGui::NewLine();
            ImGui::Text(MainMenuStrings::Toggles.c_str());
            if (ImGui::Checkbox(Button::DarknessChange.c_str(), &darkness_change_temp)) {
                Options::Settings::allow_darkness_change.SetValue(darkness_change_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::DarknessChange.c_str());
            // No Vampires/Werewolves
  
            ImGui::NewLine();
            if (ImGui::Checkbox(Button::NoVampWere.c_str(), &no_vamp_were_temp)) {
                Options::Settings::do_not_affect_supernatural.SetValue(no_vamp_were_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::NoVampWere.c_str());
            // Enable Sneak Levels

            ImGui::NewLine();
            if (ImGui::Checkbox(Button::SneakLevels.c_str(), &sneak_levels_temp)) {
                Options::Settings::sneak_level_enable.SetValue(sneak_levels_temp);
            }
            ImGui::SameLine();
            HelpMarker(Tooltip::SneakLevels.c_str());
            // Night Eye Immunity

            ImGui::NewLine();
            if (ImGui::Checkbox(Button::NightEyeImmunity.c_str(), &night_eye_immunity_temp)) {
                Options::Settings::night_eye_no_stress.SetValue(night_eye_immunity_temp);
            }
            ImGui::SameLine();
			HelpMarker(Tooltip::NightEyeImmunity.c_str());

			// Hide NPCs in Dark
			ImGui::NewLine();
			if (ImGui::Checkbox(Button::HideNPCsInDark.c_str(), &hide_npcs_in_dark_temp)) {
				Options::Settings::hide_npcs_in_dark.SetValue(hide_npcs_in_dark_temp);
			}

            //Save Config and Default Settings
            ImGui::NewLine();
            ImGui::Text(MainMenuStrings::System.c_str());
            if (ImGui::Button(MainMenuStrings::Save.c_str())) {
                Options::Settings::GetSingleton()->Update(true);
            }
            ImGui::SameLine();
            if (ImGui::Button(MainMenuStrings::Restore.c_str())) {
                RestoreDefaultSettings(false, true);
            }
            FontAwesome::Pop();

        }
    }
    

	
}


