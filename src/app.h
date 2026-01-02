#pragma once

#include <GLFW/glfw3.h>
#include <freetype/freetype.h>


class MyClass {
public:
    GLFWwindow* window;
    
    int create_window();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void run();
    void do_something();
};