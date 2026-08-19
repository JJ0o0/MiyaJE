#include <miya/core/engine.hpp>

#include <miya/platform/window.hpp>

#include <miya/core/logging/log.hpp>

namespace miya {
    Engine::Engine() = default;
    Engine::~Engine() = default;

    bool Engine::Initialize() {
        Log::Info("Initializing...");

        WindowProperties properties {
            .Title = "MiyaJE Engine",
            .Width = 800,
            .Height = 600
        };

        m_window = std::make_unique<Window>();
        if (!m_window->Initialize(properties)) {
            Log::Error("Could not initialize window");

            m_window.reset();
            return false;
        }

        m_window->SetInput(&m_input);

        m_running = true;
        return true;
    }

    void Engine::Run() {
        m_time.Reset();

        while (m_running && !m_window->ShouldClose()) {
            m_time.Tick();

            m_input.BeginFrame();
            m_window->PollEvents();

            m_window->SwapBuffers();
        }
    }

    void Engine::Shutdown() {
        Log::Info("Shutting down...");

        m_window.reset();
        m_running = false;

        Log::Info("Goodbye");
    }
}