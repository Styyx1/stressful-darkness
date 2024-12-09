#include "settings.h"

void Settings::LoadSettings() noexcept
{
	logs::info("loading settings...");
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(R"(.\Data\SKSE\Plugins\stressful-darkness.ini)");

	frame_count = (float)ini.GetDoubleValue("General", "fFrameCount", 60.0f);
	increase_amount = (float)ini.GetDoubleValue("General", "fStressIncrease", 15.0f);
	stress_message = ini.GetValue("General", "sStressMessage", "The darkness here is overwhelming...");
	light_threshold = (std::int32_t)ini.GetDoubleValue("General", "iLightTickCount", 60);
	light_level_limit = (float)ini.GetDoubleValue("General", "fLightLevelThreshold", 80.0f);
	allow_darkness_change = ini.GetBoolValue("General", "bAllowDarknessChange", true);

	logs::info("...settings loaded");
}
void Settings::LoadForms()
{
	logs::info("loading forms...");

	const int stress_global_form = 0x801;
	const int stress_enabled_form = 0x8a5;
	const char* mod_name = "Stress and Fear.esp";
	const int imod_form = 0x1AA31;
	const char* imod_name = "Dawnguard.esm";
	const auto dh = RE::TESDataHandler::GetSingleton();

	imod = dh->LookupForm(imod_form, imod_name)->As<RE::TESImageSpaceModifier>();
	stress_global = dh->LookupForm(stress_global_form, mod_name)->As<RE::TESGlobal>();
	logs::debug("loaded {} with a value of {}", stress_global->GetFormEditorID(), stress_global->value);
	stress_enabled_global = dh->LookupForm(stress_enabled_form, mod_name)->As<RE::TESGlobal>();
	logs::debug("loaded {} with a value of {}", stress_enabled_global->GetFormEditorID(), stress_enabled_global->value);

	logs::info("...loaded forms");
}

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

