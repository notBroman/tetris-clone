cmake_minimum_required(VERSION 3.28)
project(tetris-clone)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 3.4 REQUIRED)

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(
        googletest
)

add_subdirectory(shaders)
add_subdirectory(src)

target_link_libraries(tetris-clone renderer)
target_link_libraries(tetris-clone arena)
target_link_libraries(tetris-clone block)

add_dependencies(tetris-clone shaders)

add_subdirectory(tests)

