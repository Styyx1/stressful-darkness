#pragma once

namespace Hooks
{
	void InstallHooks();

    class MainUpdate
    {
    public:
        static void PlayerUpdate(RE::PlayerCharacter* p, float a_delta);
        static void InstallUpdate();

        static inline float frameCount = 0;
        static inline std::int32_t lightLevelCount;
        static void AddStress(RE::TESGlobal* a_stress);
        static void ChangeImod(RE::PlayerCharacter* player);

    private: 
        inline static REL::Relocation<decltype(&PlayerUpdate)> v_func;

    };
}