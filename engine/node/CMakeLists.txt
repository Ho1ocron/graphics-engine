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
