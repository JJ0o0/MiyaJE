#include <miya/core/time.hpp>

namespace miya {
    void Time::Reset() {
        auto now = Clock::now();
        m_startTime = now;
        m_previousTime = now;
        
        m_deltaTime = 0.0f;
        m_frameCount = 0;

        m_fpsTimer = 0.0f;
        m_framesThisSecond = 0;
        m_fps = 0;
    }

    void Time::Tick() {
        auto now = Clock::now();

        std::chrono::duration<float> delta = now - m_previousTime;
        m_deltaTime = delta.count();

        m_previousTime = now;
        m_frameCount++;

        m_fpsTimer += m_deltaTime;
        m_framesThisSecond++;

        if (m_fpsTimer >= 1.0f) {
            m_fps = static_cast<uint32_t>(static_cast<float>(m_framesThisSecond) / m_fpsTimer);
            m_fpsTimer = 0.0f;
            m_framesThisSecond = 0;
        }
    }

    float Time::GetDeltaTime() const { return m_deltaTime; }

    double Time::GetElapsedTime() const {
        auto now = Clock::now();
        std::chrono::duration<double> elapsed = now - m_startTime;
        return elapsed.count();
    }

    uint32_t Time::GetFPS() const { return m_fps; }

    uint64_t Time::GetFrameCount() const { return m_frameCount; }
}