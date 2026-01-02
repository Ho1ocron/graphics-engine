#pragma once

#include <string>
#include <map>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class MyClass {
public:
    GLFWwindow* window;
    
    int create_window();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void load_font(const std::string& font_path);
    void run();
    void do_something();
};