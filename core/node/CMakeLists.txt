add_library(label STATIC
    label/include/label.h
    label/src/label.cpp
)
target_include_directories(label
    PUBLIC label/include/
)
target_link_libraries(label PUBLIC
    font
    resource_manager
)

add_library(camera STATIC
    camera/include/camera.h
    camera/src/camera.cpp
)
target_include_directories(camera
    PUBLIC camera/include/
)

target_link_libraries(camera PUBLIC glm)
