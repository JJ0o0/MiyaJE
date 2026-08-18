add_executable(MiyaJESandbox
    "src/main.cpp"
)

target_link_libraries(MiyaJESandbox
    PRIVATE
        MiyaJEEngine
)

add_custom_command(
    TARGET MiyaJESandbox
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:MiyaJESandbox>/Assets"

    COMMENT "Copying MiyaJE assets to Sandbox..."
)