#pragma once
#include "settings.h"

namespace Utility
{
	inline static std::vector<std::string> is_a_dungeon{
		"LocTypeDungeon",
		"LocTypeDwarvenAutomatons",
		"LocTypeAnimalDen",
		"LocTypeBanditCamp",
		"LocTypeDragonPriestLair",
		"LocTypeDraugrCrypt",
		"LocTypeFalmerHive",
		"LocTypeForswornCamp",
		"LocTypeGiantCamp",
		"LocTypeHagravenNest",
		"LocTypeVampireLair",
		"LocTypeWarlockLair",
		"LocTypeWerewolfLair"};

	inline static bool IsDungeon(RE::TESObjectCELL *a_cell)
	{
		auto loc = a_cell->GetLocation();
		if (loc && loc->HasAnyKeywordByEditorID(is_a_dungeon) && a_cell->IsInteriorCell())
		{
			return true;
		}
		else
			return false;
	}

	inline static bool IsBeastForm()
	{
		RE::MenuControls *MenuControls = RE::MenuControls::GetSingleton();
		return MenuControls->InBeastForm();
	}

	inline static bool IsSuperNatural(RE::PlayerCharacter *player)
	{
		bool is_monster = IsBeastForm() || player->GetRace()->HasKeywordString("ActorTypeUndead") || player->HasKeywordString("ActorTypeUndead");

		return Options::Values::do_not_affect_supernatural.GetValue() && is_monster;
	}

	inline static float StressGain()
	{
		float result = Options::Values::increase_amount.GetValue();

		if (Options::Values::sneak_level_enable.GetValue())
		{
			RE::PlayerCharacter *player = RE::PlayerCharacter::GetSingleton();
			auto sneak_level = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kSneak);
			if (sneak_level > 30)
			{
				float modifier = 1 - sneak_level / 100;
				float minimum = 0.3f;
				float maximum = 0.9f;
				result *= std::min(std::max(modifier, minimum), maximum);
			}
		}
		return result;
	}
}