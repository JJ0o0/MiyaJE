cmake_minimum_required(VERSION 3.20)
project(
    MiyaJE
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMake/dependencies.cmake)

add_subdirectory(Engine)
add_subdirectory(Sandbox)