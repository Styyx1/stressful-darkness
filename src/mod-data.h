#pragma once

namespace MOD {
	constexpr std::string_view IMOD_MOD_NAME = "Dawnguard.esm";
	constexpr std::string_view TOML_PATH_DEFAULT = "Data/SKSE/Plugins/stressful-darkness.toml";
	constexpr std::string_view TOML_PATH_CUSTOM = "Data/SKSE/Plugins/stressful-darkness_custom.toml";
	constexpr std::string_view STRESS_MOD_NAME = "Stress and Fear.esp";

	constexpr uint32_t STRESS_GLOBAL_FORM_ID = 0x801;
	constexpr uint32_t STRESS_ENABLED_FORM_ID = 0x8a5;
	constexpr uint32_t IMOD_FORM_ID = 0x1AA31;

	constexpr std::string_view SETTINGS_SECTION = "Settings";
	constexpr std::string_view TOGGLES_SECTION = "Toggles";
	constexpr std::string_view TEXT_SECTION = "Text";	
}
