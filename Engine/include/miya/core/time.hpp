#pragma once

#include <cstdint>
#include <chrono>

namespace miya {
    class Time {
        public:
            void Reset();
            void Tick();

            float GetDeltaTime() const;
            double GetElapsedTime() const;
            uint32_t GetFPS() const;
            uint64_t GetFrameCount() const;
        private:
            using Clock = std::chrono::steady_clock;

            Clock::time_point m_startTime;
            Clock::time_point m_previousTime;

            float m_deltaTime = 0.0f;
            uint64_t m_frameCount = 0;

            float m_fpsTimer = 0.0f;
            uint32_t m_framesThisSecond = 0;
            uint32_t m_fps = 0;
    };
}