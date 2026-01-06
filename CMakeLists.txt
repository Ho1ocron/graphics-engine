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
add_subdirectory(glfw/)
add_subdirectory(freetype/)
add_subdirectory(glm/)
add_library(glad STATIC
    glad/src/glad.c
)
target_include_directories(glad
    PUBLIC glad/include/
)
# our code
add_subdirectory(engine/math/)
add_subdirectory(engine/render/)
add_subdirectory(engine/font/)
add_subdirectory(engine/resource_manager/)
add_subdirectory(engine/node/)

add_library(globals INTERFACE
    engine/constants.h
)
target_include_directories(globals PUBLIC
    INTERFACE engine/
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
