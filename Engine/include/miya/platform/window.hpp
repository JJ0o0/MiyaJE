#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace miya {
    class Input;

    enum class CursorMode {
        Normal,
        Hidden,
        Locked
    };

    struct WindowProperties {
        std::string Title = "MiyaJE Engine";
        uint32_t Width = 800;
        uint32_t Height = 600;
        bool VSync = true;
    };

    class Window {
        public:
            Window();
            ~Window();

            bool Initialize(const WindowProperties& properties = {});
            void Destroy();

            void SetInput(Input* input);

            void SwapBuffers() const;
            void PollEvents() const;

            bool ShouldClose() const;

            uint32_t GetWidth() const;
            uint32_t GetHeight() const;

            uint32_t GetFramebufferWidth() const;
            uint32_t GetFramebufferHeight() const;

            void ToggleVSync();
            void SetVSync(bool enabled);
            bool IsVSyncEnabled() const;

            void SetCursorMode(CursorMode mode);
            CursorMode GetCursorMode() const;

            void* GetNativeHandle() const;
        private:
            struct Impl;
            std::unique_ptr<Impl> m_impl;
    };
}