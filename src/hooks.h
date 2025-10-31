#pragma once

namespace Hooks
{
    static bool inside = true;
    struct MainUpdate
    {    
        static void PlayerUpdate(RE::PlayerCharacter *player, float a_delta);
        static inline float frameCount = 0;
        static inline std::int32_t lightLevelCount;
        static void AddStress(RE::TESGlobal *a_stress);
        static void ChangeImod(RE::PlayerCharacter *player);
        static bool isInside(RE::PlayerCharacter *player);
        static bool CanAddStress();
        static float GetCurrentStress();
        static bool ShouldIncreaseStress(RE::PlayerCharacter* player);


    private:
		inline static REL::HookVFT _Hook0{VTABLE_PlayerCharacter[0], 0xAD, PlayerUpdate};
    };

    class Timer
    {
    public:
        void Start();
        void Stop();
        void Reset();
        double ElapsedSeconds() const;
        bool IsRunning() const;

    private:
        std::chrono::steady_clock::time_point startTime{};
        bool running{false};
    };
}