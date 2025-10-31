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
        }
        if (a_toggles) {
            ToggleMenu::darkness_change_temp = Options::Settings::allow_darkness_change.GetValue();
            ToggleMenu::no_vamp_were_temp = Options::Settings::do_not_affect_supernatural.GetValue();
            ToggleMenu::sneak_levels_temp = Options::Settings::sneak_level_enable.GetValue();
            ToggleMenu::sneak_eye_immunity_temp = Options::Settings::night_eye_no_stress.GetValue();            
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
        }
        if(a_toggles) {
            darkness_change_temp = true;
            set::allow_darkness_change.SetValue(darkness_change_temp);
            no_vamp_were_temp = false;
            set::do_not_affect_supernatural.SetValue(no_vamp_were_temp);
            sneak_levels_temp = false;
            set::sneak_level_enable.SetValue(sneak_levels_temp);
            sneak_eye_immunity_temp = false;
            set::night_eye_no_stress.SetValue(sneak_eye_immunity_temp);
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
            FontAwesome::Pop();
            ImGui::SameLine();
            HelpMarker(Tooltip::LightLevelThreshold.c_str());

			// Stress Increase
            FontAwesome::PushSolid();
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::StressIncreaseValue.c_str(), &stress_increase_temp, 5.0, 50.0, "%.0f")) {
                Options::Settings::increase_amount.SetValue(stress_increase_temp);
            }
            FontAwesome::Pop();
            ImGui::SameLine();
			HelpMarker(Tooltip::StressIncreaseValue.c_str());

            // Stress Time
            FontAwesome::PushSolid();
            ImGui::NewLine();
            ImGui::SetNextItemWidth(300.0f);
            if (ImGui::SliderFloat(Button::StressTime.c_str(), &stress_time_temp, 20.0, 600.0, "%.2f")) {
                Options::Settings::stress_increase_seconds.SetValue(stress_time_temp);
            }
            FontAwesome::Pop();
			ImGui::SameLine();
			HelpMarker(Tooltip::StressTime.c_str());

            //Save Config and Default Settings
            FontAwesome::PushSolid();
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
            bool darkness_change = Options::Settings::allow_darkness_change.GetValue();
            if (ImGui::Checkbox(Button::DarknessChange.c_str(), &darkness_change)) {
                Options::Settings::allow_darkness_change.SetValue(darkness_change);
            }
            FontAwesome::Pop();
            ImGui::SameLine();
            HelpMarker(Tooltip::DarknessChange.c_str());
            // No Vampires/Werewolves
            FontAwesome::PushSolid();
            ImGui::NewLine();
            bool no_vamp_were = Options::Settings::do_not_affect_supernatural.GetValue();
            if (ImGui::Checkbox(Button::NoVampWere.c_str(), &no_vamp_were)) {
                Options::Settings::do_not_affect_supernatural.SetValue(no_vamp_were);
            }
            FontAwesome::Pop();
            ImGui::SameLine();
            HelpMarker(Tooltip::NoVampWere.c_str());
            // Enable Sneak Levels
            FontAwesome::PushSolid();
            ImGui::NewLine();
            bool sneak_levels = Options::Settings::sneak_level_enable.GetValue();
            if (ImGui::Checkbox(Button::SneakLevels.c_str(), &sneak_levels)) {
                Options::Settings::sneak_level_enable.SetValue(sneak_levels);
            }
            FontAwesome::Pop();
            ImGui::SameLine();
            HelpMarker(Tooltip::SneakLevels.c_str());
            // Night Eye Immunity
            FontAwesome::PushSolid();
            ImGui::NewLine();
            bool sneak_eye_immunity = Options::Settings::night_eye_no_stress.GetValue();
            if (ImGui::Checkbox(Button::SneakEyeImmunity.c_str(), &sneak_eye_immunity)) {
                Options::Settings::night_eye_no_stress.SetValue(sneak_eye_immunity);
            }
            FontAwesome::Pop();
            ImGui::SameLine();
			HelpMarker(Tooltip::SneakEyeImmunity.c_str());

            //Save Config and Default Settings
            FontAwesome::PushSolid();
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


