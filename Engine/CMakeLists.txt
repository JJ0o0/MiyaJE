add_library(MiyaJEEngine STATIC
    "src/core/engine.cpp"
    "src/core/time.cpp"
    "src/core/logging/log.cpp"
    "src/core/debug/debug_ui.cpp"
    "src/core/io/filesystem.cpp"
    
    "src/input/input.cpp"

    "src/platform/window.cpp"

    "src/graphics/opengl/gl_context.cpp"
)

target_include_directories(MiyaJEEngine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(MiyaJEEngine
    PRIVATE
        glfw
        glad
        imgui
)

target_compile_definitions(MiyaJEEngine
    PUBLIC
        $<$<CONFIG:Debug>:MIYA_DEBUG>
)