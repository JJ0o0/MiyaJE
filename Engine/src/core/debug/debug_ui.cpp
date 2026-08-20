#include <miya/core/debug/debug_ui.hpp>

#include <miya/core/logging/log.hpp>
#include <miya/platform/window.hpp>
#include <miya/input/input.hpp>
#include <miya/core/time.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace miya {
    bool DebugUI::Initialize(Window& window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        auto* windowHandle = static_cast<GLFWwindow*>(window.GetNativeHandle());
        if (!ImGui_ImplGlfw_InitForOpenGL(windowHandle, true)) {
            Log::Error("Couldn't initialize ImGui GLFW backend");
            ImGui::DestroyContext();

            return false;
        }

        if (!ImGui_ImplOpenGL3_Init("#version 460 core")) {
            Log::Error("Couldn't initialize ImGui OpenGL backend");
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            return false;
        }

        m_initiliazed = true;

        Log::Info("Initialized Dear ImGui");
        return true;
    }

    void DebugUI::Shutdown() {
        if (!m_initiliazed) return;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        m_initiliazed = false;
        Log::Info("Shutdown Dear ImGui");
    }

    void DebugUI::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
    }

    void DebugUI::Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DebugUI::Draw(
        Window& window, 
        const Time& time, 
        const Input& input
    ) {
        drawMainMenuBar();
        if (m_showStatistics) drawStatisticsWindow(time);
        if (m_showWindow) drawWindowWindow(window);
        if (m_showInput) drawInputWindow(input);
        if (m_showDemoWindow) ImGui::ShowDemoWindow(&m_showDemoWindow);
    }

    void DebugUI::drawMainMenuBar() {
        if (!ImGui::BeginMainMenuBar()) return;

        if (ImGui::BeginMenu("MiyaJE")) {
            ImGui::TextDisabled("MiyaJE Engine");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Debug")) {
            ImGui::MenuItem("Statistics", nullptr, &m_showStatistics);
            ImGui::MenuItem("Window", nullptr, &m_showWindow);
            ImGui::MenuItem("Input", nullptr, &m_showInput);
            ImGui::Separator();

            ImGui::MenuItem("ImGui Demo", nullptr, &m_showDemoWindow);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    void DebugUI::drawStatisticsWindow(const Time& time) {
        ImGui::Begin("Statistics", &m_showStatistics);
            ImGui::Text("FPS: %u", time.GetFPS());
            ImGui::Text("Delta Time: %.3fms", time.GetDeltaTime() * 1000.0f);
            ImGui::Text("Elapsed Time: %.2fs", time.GetElapsedTime());
            ImGui::Text("Frame: %llu", static_cast<unsigned long long>(time.GetFrameCount()));
        ImGui::End();
    }

    void DebugUI::drawWindowWindow(Window& window) {
        ImGui::Begin("Window", &m_showWindow);
            ImGui::Text("Size: %ux%u", window.GetWidth(), window.GetHeight());
            ImGui::Text("Framebuffer: %ux%u", window.GetFramebufferWidth(), window.GetFramebufferHeight());
            
            bool vsync = window.IsVSyncEnabled();
            if (ImGui::Checkbox("VSync", &vsync)) window.SetVSync(vsync);
            ImGui::Separator();

            ImGui::Text("Cursor");
            if (ImGui::Button("Normal")) window.SetCursorMode(CursorMode::Normal);
            ImGui::SameLine();
            if (ImGui::Button("Hidden")) window.SetCursorMode(CursorMode::Hidden);
            ImGui::SameLine();
            if (ImGui::Button("Locked")) window.SetCursorMode(CursorMode::Locked);
        ImGui::End();
    }

    void DebugUI::drawInputWindow(const Input& input) {
        ImGui::Begin("Input", &m_showInput);
            math::Vec2 mousePos = input.GetMousePosition();
            math::Vec2 mouseDelta = input.GetMouseDelta();
            math::Vec2 scrollDelta = input.GetScrollDelta();

            ImGui::Text("Mouse: %.0f, %.0f", mousePos.x, mousePos.y);
            ImGui::Text("Mouse Delta: %.0f, %.0f", mouseDelta.x, mouseDelta.y);
            ImGui::Text("Scroll: %.0f, %.0f", scrollDelta.x, scrollDelta.y);
        ImGui::End();
    }
}