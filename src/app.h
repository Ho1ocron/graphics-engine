#pragma once

#include <string>
#include <map>

#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


// struct Character {
//     unsigned int TextureID;
//     glm::ivec2   Size;
//     glm::ivec2   Bearing;
//     unsigned int Advance;
// };


class MyClass {
public:
    GLFWwindow* window;

    // std::map<char, Character> Characters;
    
    int create_window();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void load_font(const std::string& font_path);
    void run();
    void do_something();
};