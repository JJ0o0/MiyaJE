#pragma once

namespace miya {
    class Time;
    class Window;
    class Input;
    class DebugUI {
        public:
            bool Initialize(Window& window);
            void Shutdown();    
        
            void BeginFrame();
            void Render();

            void Draw(
                Window& window, 
                const Time& time, 
                const Input& input
            );
        private:
            bool m_initiliazed = false;

            bool m_showStatistics = false;
            bool m_showWindow = false;
            bool m_showInput = false;
            bool m_showDemoWindow = false;

            void drawMainMenuBar();
            void drawStatisticsWindow(const Time& time);
            void drawWindowWindow(Window& window);
            void drawInputWindow(const Input& input);
    };
}