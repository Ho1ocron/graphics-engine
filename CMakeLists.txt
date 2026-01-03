cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(graphics-engine)

# file(COPY
#     ${PROJECT_SOURCE_DIR}/assets/fonts/JetBrainsMono-Italic.ttf
#     DESTINATION ${CMAKE_BINARY_DIR}
# )

add_subdirectory(glfw/)
add_subdirectory(freetype/)
add_subdirectory(glm/)

add_library(math STATIC
    src/math/src/vector2.cpp
    src/math/src/vector3.cpp  
)

add_library(glad STATIC 
    glad/src/glad.c
)

target_include_directories(math PUBLIC
    ${PROJECT_SOURCE_DIR}/src/math/include
)

target_include_directories(glad PUBLIC
    ${PROJECT_SOURCE_DIR}/glad/include
)

# target_include_directories(shaders PUBLIC 
#     ${PROJECT_SOURCE_DIR}/src/shaders/include
# )

add_executable(graphics-engine
    src/main.cpp
    src/app.cpp
)

target_compile_definitions(graphics-engine PRIVATE
    SHADER_DIR="${PROJECT_SOURCE_DIR}/assets/shaders/"
    FONT_DIR="${PROJECT_SOURCE_DIR}/assets/fonts/"
)

target_include_directories(${PROJECT_NAME} PRIVATE glfw freetype glm)
# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(graphics-engine PRIVATE math glfw glad freetype glm "-framework OpenGL")

