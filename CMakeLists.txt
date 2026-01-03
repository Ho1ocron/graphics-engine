cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(graphics-engine)

# file(COPY
#     ${PROJECT_SOURCE_DIR}/assets/fonts/JetBrainsMono-Italic.ttf
#     DESTINATION ${CMAKE_BINARY_DIR}
# )

add_subdirectory(glfw/)
add_subdirectory(freetype/)
add_subdirectory(glm/)

add_library(math STATIC
    engine/math/src/vector2.cpp
    engine/math/src/vector3.cpp  
)

add_library(glad STATIC 
    glad/src/glad.c
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/engine/math/include
)

target_include_directories(glad PUBLIC
    ${PROJECT_SOURCE_DIR}/glad/include
)

# target_include_directories(shaders PUBLIC 
#     ${PROJECT_SOURCE_DIR}/src/shaders/include
# )
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_executable(graphics-engine
    engine/main.cpp
    engine/app.cpp
    engine/text.cpp
)
add_dependencies(graphics-engine copy_assets)
target_compile_definitions(graphics-engine PRIVATE
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)

target_include_directories(${PROJECT_NAME} PRIVATE glfw freetype glm)
# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(graphics-engine PRIVATE math glfw glad freetype glm "-framework OpenGL") 