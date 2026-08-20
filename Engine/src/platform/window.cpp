#include <miya/platform/window.hpp>

#include <miya/input/input.hpp>
#include <miya/input/key.hpp>
#include <miya/input/mouse_button.hpp>

#include <miya/core/logging/log.hpp>
#include <miya/core/debug/assert.hpp>

#include <GLFW/glfw3.h>

namespace miya {
    static Key ToMiyaKey(int key) {
        switch (key) {
            case GLFW_KEY_Q: return Key::Q;
            case GLFW_KEY_W: return Key::W;
            case GLFW_KEY_E: return Key::E;
            case GLFW_KEY_R: return Key::R;
            case GLFW_KEY_T: return Key::T;
            case GLFW_KEY_Y: return Key::Y;
            case GLFW_KEY_U: return Key::U;
            case GLFW_KEY_I: return Key::I;
            case GLFW_KEY_O: return Key::O;
            case GLFW_KEY_P: return Key::P;

            case GLFW_KEY_A: return Key::A;
            case GLFW_KEY_S: return Key::S;
            case GLFW_KEY_D: return Key::D;
            case GLFW_KEY_F: return Key::F;
            case GLFW_KEY_G: return Key::G;
            case GLFW_KEY_H: return Key::H;
            case GLFW_KEY_J: return Key::J;
            case GLFW_KEY_K: return Key::K;
            case GLFW_KEY_L: return Key::L;

            case GLFW_KEY_Z: return Key::Z;
            case GLFW_KEY_X: return Key::X;
            case GLFW_KEY_C: return Key::C;
            case GLFW_KEY_V: return Key::V;
            case GLFW_KEY_B: return Key::B;
            case GLFW_KEY_N: return Key::N;
            case GLFW_KEY_M: return Key::M;

            case GLFW_KEY_1: return Key::One;
            case GLFW_KEY_2: return Key::Two;
            case GLFW_KEY_3: return Key::Three;
            case GLFW_KEY_4: return Key::Four;
            case GLFW_KEY_5: return Key::Five;
            case GLFW_KEY_6: return Key::Six;
            case GLFW_KEY_7: return Key::Seven;
            case GLFW_KEY_8: return Key::Eight;
            case GLFW_KEY_9: return Key::Nine;
            case GLFW_KEY_0: return Key::Zero;

            case GLFW_KEY_F1: return Key::F1;
            case GLFW_KEY_F2: return Key::F2;
            case GLFW_KEY_F3: return Key::F3;
            case GLFW_KEY_F4: return Key::F4;
            case GLFW_KEY_F5: return Key::F5;
            case GLFW_KEY_F6: return Key::F6;
            case GLFW_KEY_F7: return Key::F7;
            case GLFW_KEY_F8: return Key::F8;
            case GLFW_KEY_F9: return Key::F9;
            case GLFW_KEY_F10: return Key::F10;
            case GLFW_KEY_F11: return Key::F11;
            case GLFW_KEY_F12: return Key::F12;

            case GLFW_KEY_LEFT_SHIFT: return Key::LeftShift;
            case GLFW_KEY_RIGHT_SHIFT: return Key::RightShift;

            case GLFW_KEY_LEFT_CONTROL: return Key::LeftControl;
            case GLFW_KEY_RIGHT_CONTROL: return Key::RightControl;

            case GLFW_KEY_LEFT_ALT: return Key::LeftAlt;
            case GLFW_KEY_RIGHT_ALT: return Key::RightAlt;

            case GLFW_KEY_LEFT_SUPER: return Key::LeftSuper;
            case GLFW_KEY_RIGHT_SUPER: return Key::RightSuper;

            case GLFW_KEY_ENTER: return Key::Enter;
            case GLFW_KEY_SPACE: return Key::Space;
            case GLFW_KEY_ESCAPE: return Key::Escape;
            case GLFW_KEY_TAB: return Key::Tab;
            case GLFW_KEY_BACKSPACE: return Key::Backspace;
            case GLFW_KEY_DELETE: return Key::Delete;
            case GLFW_KEY_INSERT: return Key::Insert;

            case GLFW_KEY_UP: return Key::Up;
            case GLFW_KEY_DOWN: return Key::Down;
            case GLFW_KEY_LEFT: return Key::Left;
            case GLFW_KEY_RIGHT: return Key::Right;

            case GLFW_KEY_HOME: return Key::Home;
            case GLFW_KEY_END: return Key::End;
            case GLFW_KEY_PAGE_UP: return Key::PageUp;
            case GLFW_KEY_PAGE_DOWN: return Key::PageDown;

            case GLFW_KEY_CAPS_LOCK: return Key::CapsLock;
            case GLFW_KEY_NUM_LOCK: return Key::NumLock;
            case GLFW_KEY_SCROLL_LOCK: return Key::ScrollLock;

            case GLFW_KEY_APOSTROPHE: return Key::Apostrophe;
            case GLFW_KEY_COMMA: return Key::Comma;
            case GLFW_KEY_MINUS: return Key::Minus;
            case GLFW_KEY_PERIOD: return Key::Period;
            case GLFW_KEY_SLASH: return Key::Slash;
            case GLFW_KEY_SEMICOLON: return Key::Semicolon;
            case GLFW_KEY_EQUAL: return Key::Equal;
            case GLFW_KEY_LEFT_BRACKET: return Key::LeftBracket;
            case GLFW_KEY_BACKSLASH: return Key::Backslash;
            case GLFW_KEY_RIGHT_BRACKET: return Key::RightBracket;
            case GLFW_KEY_GRAVE_ACCENT: return Key::GraveAccent;

            case GLFW_KEY_WORLD_1: return Key::World1;
            case GLFW_KEY_WORLD_2: return Key::World2;

            default: return Key::Unknown;
        }
    }

    static MouseButton ToMiyaMouseButton(int button) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
            case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
            case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;

            case GLFW_MOUSE_BUTTON_4: return MouseButton::Button4;
            case GLFW_MOUSE_BUTTON_5: return MouseButton::Button5;
            case GLFW_MOUSE_BUTTON_6: return MouseButton::Button6;
            case GLFW_MOUSE_BUTTON_7: return MouseButton::Button7;
            case GLFW_MOUSE_BUTTON_8: return MouseButton::Button8;

            default: return MouseButton::Count;
        }
    }

    struct Window::Impl {
        GLFWwindow* Handle = nullptr;
        WindowProperties Properties;

        uint32_t FramebufferWidth = 0;
        uint32_t FramebufferHeight = 0;

        bool VSync = true;

        Input* InputSystem = nullptr;
        CursorMode Cursor = CursorMode::Normal;

        static void WindowSizeCallback(GLFWwindow* glfwWindow, int width, int height) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl) return;

            impl->Properties.Width = static_cast<uint32_t>(width);
            impl->Properties.Height = static_cast<uint32_t>(height);
        }

        static void FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl) return;

            impl->FramebufferWidth = static_cast<uint32_t>(width);
            impl->FramebufferHeight = static_cast<uint32_t>(height);
        }

        static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl || !impl->InputSystem) return;

            Key miyaKey = ToMiyaKey(key);
            if (miyaKey == Key::Unknown) return;

            if (action == GLFW_PRESS) impl->InputSystem->SetKeyState(miyaKey, true);
            if (action == GLFW_RELEASE) impl->InputSystem->SetKeyState(miyaKey, false);
        }

        static void MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl || !impl->InputSystem) return;

            MouseButton miyaButton = ToMiyaMouseButton(button);
            if (miyaButton == MouseButton::Count) return;

            if (action == GLFW_PRESS) impl->InputSystem->SetMouseButtonState(miyaButton, true);
            if (action == GLFW_RELEASE) impl->InputSystem->SetMouseButtonState(miyaButton, false);
        }

        static void CursorPositionCallback(GLFWwindow* glfwWindow, double x, double y) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl || !impl->InputSystem) return;

            impl->InputSystem->SetMousePosition(math::Vec2{
                static_cast<float>(x),
                static_cast<float>(y),
            });
        }

        static void ScrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl || !impl->InputSystem) return;

            impl->InputSystem->AddScrollDelta(math::Vec2{
                static_cast<float>(xOffset),
                static_cast<float>(yOffset),
            });
        }

        static void WindowFocusCallback(GLFWwindow* glfwWindow, int focused) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
            if (!impl || !impl->InputSystem) return;

            if (!focused) impl->InputSystem->Reset();
        }
    };

    static void errorCallback(int code, const char* description) {
        miya::Log::Error("GLFW Error [{}]: {}", code, description);
    }

    Window::Window() : m_impl(std::make_unique<Impl>()) {}
    Window::~Window() { Destroy(); }

    bool Window::Initialize(const WindowProperties& properties) {
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit()) {
            Log::Error("Could not initialize GLFW");
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef MIYA_DEBUG
            glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
        #endif

        m_impl->Handle = glfwCreateWindow(
            static_cast<int>(properties.Width),
            static_cast<int>(properties.Height),
            properties.Title.c_str(),
            nullptr, nullptr
        );

        if (!m_impl->Handle) {
            Log::Error("Could not create window");

            glfwTerminate();
            return false;
        }

        m_impl->Properties = properties;

        glfwSetWindowUserPointer(m_impl->Handle, m_impl.get());
        glfwSetWindowSizeCallback(m_impl->Handle, Impl::WindowSizeCallback);
        glfwSetFramebufferSizeCallback(m_impl->Handle, Impl::FramebufferSizeCallback);
        glfwSetKeyCallback(m_impl->Handle, Impl::KeyCallback);
        glfwSetMouseButtonCallback(m_impl->Handle, Impl::MouseButtonCallback);
        glfwSetCursorPosCallback(m_impl->Handle, Impl::CursorPositionCallback);
        glfwSetScrollCallback(m_impl->Handle, Impl::ScrollCallback);
        glfwSetWindowFocusCallback(m_impl->Handle, Impl::WindowFocusCallback);

        glfwMakeContextCurrent(m_impl->Handle);

        SetVSync(properties.VSync);

        int framebufferWidth, framebufferHeight = 0;
        glfwGetFramebufferSize(m_impl->Handle, &framebufferWidth, &framebufferHeight);

        m_impl->FramebufferWidth = static_cast<uint32_t>(framebufferWidth);
        m_impl->FramebufferHeight = static_cast<uint32_t>(framebufferHeight);

        Log::Info("Created window '{}' ({}x{})", properties.Title, properties.Width, properties.Height);
        return true;
    }

    void Window::Destroy() {
        if (m_impl->Handle) { 
            glfwDestroyWindow(m_impl->Handle);
            m_impl->Handle = nullptr;
        }

        glfwTerminate();
        Log::Info("Shutdown Window");
    }

    void Window::SetInput(Input* input) { m_impl->InputSystem = input; }

    void Window::SwapBuffers() const {
        MIYA_ASSERT(m_impl->Handle, "Cannot swap buffers without an initialized window");
        glfwSwapBuffers(m_impl->Handle); 
    }

    void Window::PollEvents() const { glfwPollEvents(); }

    bool Window::ShouldClose() const {
        MIYA_ASSERT(m_impl->Handle, "Cannot query window state without an initialized window");
        return glfwWindowShouldClose(m_impl->Handle); 
    }

    uint32_t Window::GetWidth() const { return m_impl->Properties.Width; }
    uint32_t Window::GetHeight() const { return m_impl->Properties.Height; }

    uint32_t Window::GetFramebufferWidth() const { return m_impl->FramebufferWidth; }
    uint32_t Window::GetFramebufferHeight() const { return m_impl->FramebufferHeight; }

    void Window::ToggleVSync() { SetVSync(!IsVSyncEnabled()); }

    void Window::SetVSync(bool enabled) {
        MIYA_ASSERT(m_impl->Handle, "Cannot set VSync without an initialized window");

        glfwSwapInterval(enabled ? 1 : 0);
        m_impl->VSync = enabled;
    }

    bool Window::IsVSyncEnabled() const { return m_impl->VSync; }

    void Window::SetCursorMode(CursorMode mode) {
        MIYA_ASSERT(m_impl->Handle, "Cannot set cursor mode without an initialized window");

        switch (mode) {
            case CursorMode::Normal:
                glfwSetInputMode(m_impl->Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                break;
            case CursorMode::Hidden:
                glfwSetInputMode(m_impl->Handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                break;
            case CursorMode::Locked:
                glfwSetInputMode(m_impl->Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                break;
        }

        m_impl->Cursor = mode;
    }

    CursorMode Window::GetCursorMode() const { return m_impl->Cursor; }

    void* Window::GetNativeHandle() const {
        MIYA_ASSERT(m_impl->Handle, "Cannot  get native handle without an initialized window");
        return m_impl->Handle;
    }
}