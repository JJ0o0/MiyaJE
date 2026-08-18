#include <miya/platform/window.hpp>

#include <miya/core/logging/log.hpp>
#include <miya/core/debug/assert.hpp>

#include <GLFW/glfw3.h>

namespace miya {
    struct Window::Impl {
        GLFWwindow* Handle = nullptr;
        WindowProperties Properties;

        uint32_t FramebufferWidth = 0;
        uint32_t FramebufferHeight = 0;

        bool VSync = true;

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
    }

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
}