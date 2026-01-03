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

add_library(text STATIC
    engine/node/text/src/text.cpp
)

add_library(collision_body STATIC
    engine/node/collision_body/src/collision_body.cpp
)

add_library(character_body_2d STATIC
    engine/node/character_body_2d/src/character_body.cpp

)

add_library(glad STATIC 
    glad/src/glad.c
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/engine/math/include
)

target_include_directories(text PUBLIC
    ${PROJECT_SOURCE_DIR}/engine/node/text/include
)

target_include_directories(collision_body PUBLIC
    ${PROJECT_SOURCE_DIR}/engine/node/collision_body/include

)

target_include_directories(character_body_2d PUBLIC
    ${PROJECT_SOURCE_DIR}/engine/node/character_body_2d/include

)

target_compile_definitions(text PUBLIC
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)

target_compile_definitions(collision_body PUBLIC
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)

target_compile_definitions(character_body_2d PUBLIC
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)

target_link_libraries(text PUBLIC glad freetype glm)
target_link_libraries(collision_body PUBLIC glad freetype glm text)
target_link_libraries(character_body_2d PUBLIC glad freetype glm text collision_body)

target_include_directories(glad PUBLIC
    ${PROJECT_SOURCE_DIR}/glad/include
)


add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_executable(graphics-engine
    engine/main.cpp
    engine/app.cpp
)

add_dependencies(graphics-engine copy_assets)

target_include_directories(graphics-engine PRIVATE
    ${PROJECT_SOURCE_DIR}/engine
)

target_compile_definitions(graphics-engine PRIVATE
    SHADER_DIR="assets/shaders/"
    FONT_DIR="assets/fonts/"
)



# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(graphics-engine PRIVATE math text collision_body character_body_2d glfw glad freetype glm "-framework OpenGL") 