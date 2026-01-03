#pragma once

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "text.h"
#include "shader.h"
#include "constants.h"


class MyApp 
{
private:
    const char* title;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    unsigned int VAO, VBO;

    std::vector<Text> texts;

    GLFWwindow* window = nullptr;

    void create_window(); 
    void setup();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void render_text();
    void processInput(GLFWwindow *window);
    
public:
    GLFWwindow* get_window() { return window; }
    void init();
    void create_text(const char* text, const char* font_path, glm::vec3 position, float font_size, float scale, glm::vec3 color);
    void run();

    MyApp(const char* app_title, const unsigned int& width, const unsigned int& height) : title(app_title), SCR_WIDTH(width), SCR_HEIGHT(height) {}
};