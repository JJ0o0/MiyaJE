add_library(MiyaJEEngine STATIC
    "src/core/engine.cpp"
    "src/core/time.cpp"
    "src/core/logging/log.cpp"

    "src/platform/window.cpp"
)

target_include_directories(MiyaJEEngine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(MiyaJEEngine
    PRIVATE
        glfw
)

target_compile_definitions(MiyaJEEngine
    PUBLIC
        $<$<CONFIG:Debug>:MIYA_DEBUG>
)