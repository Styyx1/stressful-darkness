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
		inline str LightLevelTitle = "Current Light Level";
		inline str HideNPCTitle = FontAwesome::UnicodeToUtf8(0xf070) + " NPC Fade Settings";
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
			inline str CurrentLightLevel = "Current Light Level";
			inline str StressMessage = "Stress Message";
			inline str HideNPCsInDarkStress = "Stress Threshold";
			inline str HideFullFadeDistance = "Full Fade Distance";
			inline str HideNoFadeDistance = "No Fade Distance";
			inline str NPCHideThreshold = "Light Threshold";
        };

        namespace Tooltip {
			inline str StressIncreaseValue = "Amount of stress increase each interval.";
			inline str LightLevelThreshold = "Light level below which stress will increase.";
			inline str StressTime = "Time (in seconds) spent in darkness before stress increases.";
			inline str CurrentLightLevel = "Displays the player's current light level.";
			inline str StressMessage = "Message displayed when stress is increased.";
			inline str HideNPCsInDark = "Stress level threshold for when NPCs start to fade in the distance";
			inline str HideFullFadeDistance = "Distance at which NPCs are fully faded out.";
			inline str HideNoFadeDistance = "Distance at which NPCs start to fade.";
			inline str NPCHideThreshold = "Light level threshold below which NPCs will be hidden.";
		};
        inline float stress_increase_temp;
		inline float light_level_limit_temp;
		inline float stress_time_temp;
		inline float current_light_level_temp;
		inline str stress_message_temp;
		inline int32_t npc_hide_stress_threshold_temp;
		inline float npc_hide_full_fade_distance_temp;
		inline float npc_hide_no_fade_distance_temp;
		inline float npc_hide_light_level_threshold_temp;

    }
    namespace ToggleMenu {
        void __stdcall RenderToggles();

        namespace Button {
			inline str DarknessChange = "Allow Darkness Change";
			inline str NoVampWere = "Exclude Vampires/Werewolves";
			inline str SneakLevels = "Enable Sneak Levels";
			inline str NightEyeImmunity = "Night Eye Immunity";
			inline str HideNPCsInDark = "Hide NPCs in Dark";
        }
        namespace Tooltip {
            inline str DarknessChange = "Toggle Visual changes with increased stress level";
			inline str NoVampWere = "Prevent Vampires and Werewolves from gaining stress";
			inline str SneakLevels = "Enable stress increase based on sneak level";
			inline str NightEyeImmunity = "Prevent stress increase while having a Night Eye effect active";
			inline str HideNPCsInDark = "Hide NPCs when they are in darkness beyond the light level threshold and if your stresslevel is above the threshold.";

        }
		inline bool darkness_change_temp;
		inline bool no_vamp_were_temp;
		inline bool sneak_levels_temp;
		inline bool night_eye_immunity_temp;
		inline bool hide_npcs_in_dark_temp;
	}
}

