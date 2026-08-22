#pragma once

#include <miya/core/debug/debug_ui.hpp>
#include <miya/graphics/color.hpp>
#include <miya/input/input.hpp>
#include <miya/core/time.hpp>

#include <memory>

namespace miya {
    namespace OpenGL {
        class GLContext;
    }

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
            std::unique_ptr<OpenGL::GLContext> m_glContext;

            Color m_clearColor{0.1f, 0.1f, 0.1f, 1.0f};

            Time m_time;
            Input m_input;
            DebugUI m_debugUI;
    };
}