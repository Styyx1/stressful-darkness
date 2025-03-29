#pragma once

namespace Options
{

	namespace Values
	{
		static REX::INI::F32 increase_amount{"General", "fStressIncrease", 15.0f};
		static REX::INI::F32 light_level_limit{"General", "fLightLevelThreshold", 80.0f};
		static REX::INI::Bool allow_darkness_change{"General", "bAllowDarknessChange", true};
		static REX::INI::Bool do_not_affect_supernatural{"General", "bNoVampWere", false};
		static REX::INI::Bool sneak_level_enable{"General", "bEnableSneakLevels", false};

		static REX::INI::F32 stress_increase_seconds{"General", "fSecondsTillStress", 30.0f};

		static REX::INI::Str stress_message{"General", "sStressMessage", (std::string)"The darkness here is overwhelming..."};

		static void Update()
		{
			logs::info("***************SETTINGS***************");
			logs::info("loading settings...");
			const auto ini = REX::INI::SettingStore::GetSingleton();
			ini->Init(R"(.\Data\SKSE\Plugins\stressful-darkness.ini)", R"(.\Data\SKSE\Plugins\stressful-darkness.ini)");
			ini->Load();

			//set min and max value for stress increase timer
			stress_increase_seconds.SetValue( std::clamp(stress_increase_seconds.GetValue(), 0.0f, 240.0f));

		}
	}
	struct Forms
	{
		// forms
		inline static RE::TESGlobal *stress_global{nullptr};
		inline static RE::TESGlobal *stress_enabled_global{nullptr};
		inline static RE::TESImageSpaceModifier *imod{nullptr};
		inline static void LoadForms()
		{
			logs::info("***************FORMS***************");
			logs::info("loading forms...");

			const int stress_global_form = 0x801;
			const int stress_enabled_form = 0x8a5;
			const char *mod_name = "Stress and Fear.esp";
			const int imod_form = 0x1AA31;
			const char *imod_name = "Dawnguard.esm";
			const auto dh = RE::TESDataHandler::GetSingleton();

			imod = dh->LookupForm<RE::TESImageSpaceModifier>(imod_form, imod_name);

			stress_global = dh->LookupForm<RE::TESGlobal>(stress_global_form, mod_name);
			stress_enabled_global = dh->LookupForm<RE::TESGlobal>(stress_enabled_form, mod_name);

			if (stress_global == nullptr || stress_enabled_global == nullptr)
			{
				SKSE::stl::report_and_fail("Stress and Fear is not enabled/loaded, please enable it this mod will not work without it");
			}
			else
			{
				logs::info("loaded {} with a value of {}", stress_global->GetFormEditorID(), stress_global->value);
				logs::info("loaded {} with a value of {}", stress_enabled_global->GetFormEditorID(), stress_enabled_global->value);
			}

			logs::info("...loaded forms");
		}
	};
}

// unused for now, but i will leave it here in case i want to revisit the idea of it at some point
// inline static std::unordered_map<RE::TESObjectLIGH *, RE::Color> lightStorage;

/*
Potential Imod Forms:

* Dawnguard.esm
* 0x1AA31 -- perfect


* Skyrim.esm not tested cause not needed for now. I keep it here just in case i wanna try stuff again
* 0xE3032
* 0xF756E
* 0xFD7DB -- berserk effect
* 0x10C445 -- low health
* Dragonborn.esm
* 0x317D8
*
*/