cmake_minimum_required(VERSION 3.14)

project(graphics-engine)

add_subdirectory(glfw/)
add_subdirectory(freetype/)

add_library(math STATIC
    src/math/src/vector2.cpp
    src/math/src/vector3.cpp
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/src/math/include
)

add_executable(graphics-engine
    src/main.cpp
    src/app.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE glfw freetype)
# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(graphics-engine PRIVATE math glfw freetype)

