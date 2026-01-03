#pragma once

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"
#include "constants.h"


// class MyApp 
// {
// public:
//     GLFWwindow* window;
    
//     int create_window();
//     static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//     void load_font(const char* font_path);
//     void render_font();
//     void run();
//     void do_something();

// private:
//     FT_Library library;
//     FT_Face face;
//     FT_Error error;
// };
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};


struct Font {
    std::map<GLchar, Character> characters;
};


class MyApp 
{
private:
    const char* title;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    unsigned int VAO, VBO;

    GLFWwindow* window;
    
public:
    void create_window(); 
    Font LoadFont(const std::string& path, unsigned int fontSize);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void processInput(GLFWwindow *window);
    void RenderText(Shader &shader, const Font& font, std::string text, float x, float y, float scale, glm::vec3 color);

    int run();

    MyApp(const char* app_title, const unsigned int& width, const unsigned int& height) : title(app_title), SCR_WIDTH(width), SCR_HEIGHT(height) {}
};