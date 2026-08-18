#pragma once

namespace miya {
    class Engine {
        public:
            Engine();
            ~Engine();

            void Initialize();
            void Run();
            void Shutdown();
        private:
            bool m_running = false;
    };
}