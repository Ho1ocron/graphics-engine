#pragma once

#include <GLFW/glfw3.h>


class MyClass {
public:
    GLFWwindow* window;
    
    int createWindow();
    void run();
    void doSomething();
};