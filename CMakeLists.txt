cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(graphics-engine)

add_compile_definitions(
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)

add_executable(graphics-engine
    engine/main.cpp
    engine/app.cpp
)

# third-party libs
add_subdirectory(libs/glfw/)
add_subdirectory(libs/freetype/)
add_subdirectory(libs/glm/)
add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad
    PUBLIC libs/glad/include/
)
# our code
add_subdirectory(core/math/)
add_subdirectory(core/render/)
add_subdirectory(core/font/)
add_subdirectory(core/resource_manager/)
add_subdirectory(core/node/)

add_library(globals INTERFACE
    core/constants.h
)
target_include_directories(globals PUBLIC
    INTERFACE core/
)

target_link_libraries(graphics-engine PUBLIC
    glfw
    glad
    freetype
    glm
    math
    render
    resource_manager
    font
    label
)
