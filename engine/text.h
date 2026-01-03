#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"


struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};


struct Font {
    std::map<char, Character> characters;
};


struct Text 
{
public:
    Text(
        const char* text, const char* fontPath,
        glm::vec3 position, float fontSize, float scale, 
        const unsigned int& screen_width,
        const unsigned int& screen_height,
        glm::vec3 color
    );

    void render();
    void setScreenSize(const unsigned int& width, const unsigned int& height);

private:
    void loadFont(const std::string& path, float& size);
    void setupBuffers();

    const unsigned int screen_width;
    const unsigned int screen_height;
    std::string content;
    glm::vec2 position;
    float fontSize;
    float scale;
    glm::vec3 color;

    Font font;
    Shader shader;

    unsigned int VBO{};
    unsigned int VAO{};
};