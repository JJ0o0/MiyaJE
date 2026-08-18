add_library(MiyaJEEngine STATIC
    "src/core/engine.cpp"
    "src/core/logging/log.cpp"
)

target_include_directories(MiyaJEEngine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_definitions(MiyaJEEngine
    PUBLIC
        $<$<CONFIG:Debug>:MIYA_DEBUG>
)