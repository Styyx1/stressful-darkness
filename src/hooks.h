#pragma once

namespace Hooks
{
    void InstallHooks();

    static bool inside = true;
    class MainUpdate
    {
    public:
        static void PlayerUpdate(RE::PlayerCharacter *player, float a_delta);
        static void InstallUpdate();

        static inline float frameCount = 0;
        static inline std::int32_t lightLevelCount;
        static void AddStress(RE::TESGlobal *a_stress);
        static void ChangeImod(RE::PlayerCharacter *player);
        static bool isInside(RE::PlayerCharacter *player);

    private:
        inline static REL::Relocation<decltype(&PlayerUpdate)> v_func;
    };

    class Timer
    {
    public:
        void Start();

        void Stop();

        void Reset();

        double ElapsedSeconds();

        bool IsRunning() const;

    private:
        std::chrono::steady_clock::time_point startTime{};
        bool running{false};
    };
}