#pragma once

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <optional>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "text.h"
#include "constants.h"
#include "player/player.h"


class MyApp 
{
private:
    const char* title;
    int SCR_WIDTH;
    int SCR_HEIGHT;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    unsigned int VAO, VBO;

    std::vector<std::unique_ptr<Text>> texts;

    GLFWwindow* window = nullptr;

    void create_window(); 
    void setup();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void render_text();
    
public:
    GLFWwindow* get_window() { return window; }
    void init();
    Text& create_text(const char* text, const char* font_path, glm::vec3 position, float font_size, float scale, glm::vec3 color);
    void modify_text(
        Text& text, const char* new_text, const char* new_font_path, 
        std::optional<glm::vec3> position,
        std::optional<float> font_size, std::optional<float> scale, 
        std::optional<glm::vec3> color
    );
    void run(const std::function<void()>& on_update = {});

    MyApp(const char* app_title, const unsigned int& width = 800, const unsigned int& height = 600) : title(app_title), SCR_WIDTH(width), SCR_HEIGHT(height) {}
};