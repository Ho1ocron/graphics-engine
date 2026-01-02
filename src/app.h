#pragma once

#include <GLFW/glfw3.h>


class MyClass {
public:
    GLFWwindow* window;
    
    int createWindow();
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void run();
    void doSomething();
};