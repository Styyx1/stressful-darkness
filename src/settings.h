#pragma once

class Settings
{
public:
	//settings
	inline static float frame_count;
	inline static float increase_amount;
	inline static std::int32_t light_threshold;
	inline static std::string stress_message;
	inline static float light_level_limit;
	inline static bool allow_darkness_change;

	//forms
	inline static RE::TESGlobal* stress_global;
	inline static RE::TESGlobal* stress_enabled_global;
	inline static RE::TESImageSpaceModifier* imod{nullptr};

	//unused for now, but i will leave it here in case i want to revisit the idea of it at some point
	inline static std::unordered_map<RE::TESObjectLIGH*, RE::Color> lightStorage;

	static void LoadSettings() noexcept;
	static void LoadForms();
};
