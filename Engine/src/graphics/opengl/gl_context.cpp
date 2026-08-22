#include "gl_context.hpp"

#include <miya/core/logging/log.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

namespace miya::OpenGL {
    static std::string getDebugSourceStr(GLenum src) {
        switch (src) {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION: return "Application";
            case GL_DEBUG_SOURCE_OTHER: return "Other";
            default: return "Unknown";
        }
    }

    static std::string getDebugTypeStr(GLenum type) {
        switch (type) {
            case GL_DEBUG_TYPE_ERROR: return "Error";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behaviour";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behaviour";
            case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
            case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
            case GL_DEBUG_TYPE_MARKER: return "Marker";
            case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
            case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
            case GL_DEBUG_TYPE_OTHER: return "Other";
            default: return "Unknown";
        }
    }

    static std::string getDebugSeverityStr(GLenum severity) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH: return "High";
            case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
            case GL_DEBUG_SEVERITY_LOW: return "Low";
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
            default: return "Unknown";
        }
    }

    static void APIENTRY glDebugOutput(
        GLenum src, GLenum type,
        unsigned int id,
        GLenum severity,
        GLsizei length, const char* msg, const void* userParam
    ) {
        if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

        const std::string srcStr = getDebugSourceStr(src);
        const std::string typeStr = getDebugTypeStr(type);
        const std::string severityStr = getDebugSeverityStr(severity);

        Log::Info(
            "OpenGL Error:\n"
            "Source: {}\n"
            "Type: {}\n"
            "ID: {}\n"
            "Severity: {}\n"
            "Message: {}",
            srcStr, typeStr, id, severityStr, msg
        );
    }

    bool GLContext::Initialize() {
        if (m_initialized) return true;

        if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
            Log::Error("Couldn't initialize OpenGL");
            return false;
        }

        GLint major, minor, profile = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (major != 4 || minor != 6 || profile != GL_CONTEXT_CORE_PROFILE_BIT) {
            Log::Error("Couldn't initialize OpenGL: Unsupported context {}.{}", major, minor);
            return false;
        }

        #ifdef MIYA_DEBUG
            GLint flags = 0;
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, nullptr);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            }
        #endif

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
        glFrontFace(GL_CCW);

        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        Log::Info("OpenGL: {}", version);
        Log::Info("{} - {}", vendor, renderer);

        m_initialized = true;
        return true;
    }

    void GLContext::Destroy() {
        m_initialized = false;
    }

    void GLContext::Clear(const Color& color, bool clearDepth) {
        glClearColor(color.R, color.G, color.B, color.A);
        glClear(GL_COLOR_BUFFER_BIT | (clearDepth ? GL_DEPTH_BUFFER_BIT : 0));
    }
}