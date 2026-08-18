#include <miya/core/engine.hpp>

#include <miya/core/logging/log.hpp>

namespace miya {
    void Engine::Initialize() {
        Log::Info("Initializing...");
        m_running = true;
    }

    void Engine::Run() {
        Log::Info("Running...");
        m_running = false;
    }

    void Engine::Shutdown() {
        Log::Info("Shutting down...");
        Log::Info("Goodbye");
    }
}