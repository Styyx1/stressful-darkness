#pragma once
#include "mod-data.h"

namespace Options
{
	using namespace MOD;

	struct Settings : public REX::Singleton<Settings>
	{
		inline static REX::TOML::F32 increase_amount{ SETTINGS_SECTION, "fStressIncrease", 15.0f };
		inline static REX::TOML::F32 light_level_limit{ SETTINGS_SECTION, "fLightLevelThreshold", 80.0f };
		inline static REX::TOML::F32 stress_increase_seconds{ SETTINGS_SECTION, "fSecondsTillStress", 30.0f };

		inline static REX::TOML::Bool allow_darkness_change{ TOGGLES_SECTION, "bAllowDarknessChange", true };
		inline static REX::TOML::Bool do_not_affect_supernatural{ TOGGLES_SECTION, "bNoVampWere", false };
		inline static REX::TOML::Bool sneak_level_enable{ TOGGLES_SECTION, "bEnableSneakLevels", false };
		inline static REX::TOML::Bool night_eye_no_stress{ TOGGLES_SECTION, "bNightEyeNoStress", false };

		inline static REX::TOML::Str stress_message{ TEXT_SECTION, "sStressMessage", (std::string)"The darkness here is overwhelming..." };

		void Update()
		{
			REX::INFO("loading settings...");
			const auto toml = REX::TOML::SettingStore::GetSingleton();
			toml->Init(TOML_PATH_DEFAULT.data(), TOML_PATH_CUSTOM.data());
			toml->Load();

			//set min and max value for stress increase timer
			stress_increase_seconds.SetValue(std::clamp(stress_increase_seconds.GetValue(), 0.0f, 240.0f));

		}
	};
	struct Forms : public REX::Singleton<Forms>
	{		
		// forms
		inline static RE::TESGlobal *stress_global{nullptr};
		inline static RE::TESGlobal *stress_enabled_global{nullptr};
		inline static RE::TESImageSpaceModifier *imod{nullptr};

		void LoadForms()
		{
			const auto dh = RE::TESDataHandler::GetSingleton();
			imod = dh->LookupForm<RE::TESImageSpaceModifier>(IMOD_FORM_ID, IMOD_MOD_NAME);

			stress_global = dh->LookupForm<RE::TESGlobal>(STRESS_GLOBAL_FORM_ID, STRESS_MOD_NAME);
			stress_enabled_global = dh->LookupForm<RE::TESGlobal>(STRESS_ENABLED_FORM_ID, STRESS_MOD_NAME);

			if (!stress_global || !stress_enabled_global || !stress_global->Is(RE::FormType::Global) || !stress_enabled_global->Is(RE::FormType::Global))
			{
				REX::FAIL("Stress and Fear is not enabled/loaded, please enable it this mod will not work without it");
			}
		}
	};
}