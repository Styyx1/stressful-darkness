#pragma once
#include "API/SKSEMenuFramework.h"
#include "settings.h"

namespace UI {
    using str = std::string;
    namespace MainMenuStrings {
        inline str MainTitle = "Stressful Darkness";
        inline str Settings = "Settings";
        inline str Toggles = "Toggles";
        inline str Save = FontAwesome::UnicodeToUtf8(0xf0c7) + " Save Settings";
		inline str Restore = FontAwesome::UnicodeToUtf8(0xf0e2) + " Restore Default Settings";
        inline str System = FontAwesome::UnicodeToUtf8(0xf390) + " System";
    }

    void Register();
    
    void RestoreSettingsFromConfig(bool a_settings, bool a_toggles);
    void RestoreDefaultSettings(bool a_settings, bool a_toggles);
    void HelpMarker(const char* desc);

    namespace SetMenu {
        void __stdcall RenderSettings();
        namespace Button {
			inline str StressIncreaseValue = "Stress Increase";
			inline str LightLevelThreshold = "Light Level Threshold";
			inline str StressTime = "Stress Time";
        };

        namespace Tooltip {
			inline str StressIncreaseValue = "Amount of stress increase each interval.";
			inline str LightLevelThreshold = "Light level below which stress will increase.";
			inline str StressTime = "Time (in seconds) spent in darkness before stress increases.";
        };
        inline float stress_increase_temp;
		inline float light_level_limit_temp;
		inline float stress_time_temp;

    }
    namespace ToggleMenu {
        void __stdcall RenderToggles();

        namespace Button {
			inline str DarknessChange = "Allow Darkness Change";
			inline str NoVampWere = "Exclude Vampires/Werewolves";
			inline str SneakLevels = "Enable Sneak Levels";
			inline str SneakEyeImmunity = "Night Eye Immunity";
        }
        namespace Tooltip {
            inline str DarknessChange = "Toggle Visual changes with increased stress level";
			inline str NoVampWere = "Prevent Vampires and Werewolves from gaining stress";
			inline str SneakLevels = "Enable stress increase based on sneak level";
			inline str SneakEyeImmunity = "Prevent stress increase while having a Night Eye effect active";
        }
		inline bool darkness_change_temp;
		inline bool no_vamp_were_temp;
		inline bool sneak_levels_temp;
		inline bool sneak_eye_immunity_temp;
	}
}

