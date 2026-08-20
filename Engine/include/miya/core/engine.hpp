#pragma once

#include <miya/core/debug/debug_ui.hpp>
#include <miya/input/input.hpp>
#include <miya/core/time.hpp>

#include <memory>

namespace miya {
    class Window;
    class Engine {
        public:
            Engine();
            ~Engine();

            bool Initialize();
            void Run();
            void Shutdown();
        private:
            bool m_running = false;

            std::unique_ptr<Window> m_window;

            Time m_time;
            Input m_input;
            DebugUI m_debugUI;
    };
}