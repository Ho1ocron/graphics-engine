cmake_minimum_required(VERSION 3.14)

project(graphics-engine)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/app.cpp
    src/vector3.cpp
    src/vector2.cpp
)

