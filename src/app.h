#pragma once

#include <string>
#include <map>

#include <vector3.h>
#include <vector2.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ft2build.h>

#include FT_FREETYPE_H


class MyApp 
{
public:
    GLFWwindow* window;
    
    int create_window();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void load_font(const char* font_path);
    void render_font();
    void run();
    void do_something();

private:
    FT_Library library;
    FT_Face face;
    FT_Error error;
};