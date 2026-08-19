#pragma once

#include <miya/core/time.hpp>
#include <miya/input/input.hpp>

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
    };
}