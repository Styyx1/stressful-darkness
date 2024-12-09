#pragma once
#include "settings.h"

namespace Utility
{
	inline static std::vector<std::string> is_a_dungeon
	{
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
		"LocTypeWerewolfLair"	
	};

	inline static bool IsDungeon(RE::TESObjectCELL* a_cell) {
		auto loc = a_cell->GetLocation();
		if (loc && loc->HasAnyKeywordByEditorID(is_a_dungeon) && a_cell->IsInteriorCell()) {
			return true;
		}
		else 
			return false;
	}

	inline static bool IsBeastForm()
	{
		RE::MenuControls* MenuControls = RE::MenuControls::GetSingleton();
		return MenuControls->InBeastForm();
	}

	//unused for now, but may revisit the idea of it again at some point
	inline static void DimLightsInCell(RE::TESObjectCELL* a_cell, RE::PlayerCharacter* player, bool reset, float factor)
	{	
		double radius = 25000.0;
		a_cell->ForEachReferenceInRange(player->GetPosition(), radius, [&](RE::TESObjectREFR* ref) {
			if (ref->GetBaseObject()->Is(RE::FormType::Light) || ref->Is(RE::FormType::Light)) {
				auto base = ref->GetBaseObject();
				auto& store_rad = base->As<RE::TESObjectLIGH>()->data.color;
				Settings::lightStorage.try_emplace(base->As<RE::TESObjectLIGH>(), store_rad);
				std::uint8_t minimum = 0;
				std::uint8_t maximum = 255;
				auto color_alpha = base->As<RE::TESObjectLIGH>()->data.color.blue;
				base->As<RE::TESObjectLIGH>()->data.color.red = 255;
				base->As<RE::TESObjectLIGH>()->data.color.alpha = 0;
				base->As<RE::TESObjectLIGH>()->data.color.blue = 255;
				logs::info("changed blue from {} to {}", color_alpha, base->As<RE::TESObjectLIGH>()->data.color.blue);
				;
			}
			return RE::BSContainer::ForEachResult::kContinue;
			});
	}

	//unused for now, but may revisit the idea of it again at some point
	inline static void RestoreLights(RE::TESObjectCELL* a_cell, RE::PlayerCharacter* player)
	{
		double radius = 25000.0;
		a_cell->ForEachReferenceInRange(player->GetPosition(), radius, [&](RE::TESObjectREFR* ref) {
			if (ref->GetBaseObject()->Is(RE::FormType::Light) || ref->Is(RE::FormType::Light)) {
				auto base = ref->GetBaseObject();
				if (!Settings::lightStorage.empty()){
					auto curr_light = Settings::lightStorage.at(ref->GetBaseObject()->As<RE::TESObjectLIGH>());
					base->As<RE::TESObjectLIGH>()->data.color = curr_light;
					logs::info("color alpha is reset to {}", curr_light.alpha);
					;
				}				
			}
			return RE::BSContainer::ForEachResult::kContinue;
			});
	
	}

}