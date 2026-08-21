#include <miya/core/engine.hpp>
#include <miya/core/io/filesystem.hpp>

#include <miya/platform/window.hpp>

#include <miya/core/logging/log.hpp>

namespace miya {
    Engine::Engine() = default;
    Engine::~Engine() = default;

    bool Engine::Initialize() {
        Log::Info("Initializing...");

        if (!FileSystem::SetAssetRoot("Assets")) {
            Log::Error("Couldn't initialize asset root");
            return false;
        }

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

        if (!m_debugUI.Initialize(*m_window)) {
            Log::Error("Could not initialize debug UI");
            return false;
        }

        m_running = true;
        return true;
    }

    void Engine::Run() {
        m_time.Reset();

        while (m_running && !m_window->ShouldClose()) {
            m_time.Tick();

            m_input.BeginFrame();
            m_window->PollEvents();

            m_debugUI.BeginFrame();
                m_debugUI.Draw(*m_window, m_time, m_input);
            m_debugUI.Render();

            m_window->SwapBuffers();
        }
    }

    void Engine::Shutdown() {
        Log::Info("Shutting down...");

        m_debugUI.Shutdown();
        if (m_window) m_window->Destroy();
        m_running = false;

        Log::Info("Goodbye");
    }
}