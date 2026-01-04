#pragma once

#include "character_body_2d.h"
#include "text.h"



class Player : protected CharacterBody2D
{
private:
    glm::vec3 size;
    unsigned int screen_width;
    unsigned int screen_height;

    static constexpr const char* default_font_path = FONT_DIR BOLD_FONT;


public:
    Player(
        unsigned int screen_width,
        unsigned int screen_height,
        const glm::vec3& init_position = glm::vec3{0.0f},
        const char* text = "@",
        const char* font_path = default_font_path,
        float font_size = 48.0f,
        float scale = 1.0f,
        const glm::vec3& color = glm::vec3{1.0f}
    )
    : CharacterBody2D(
        std::make_unique<Text>(
            text,
            font_path,
            init_position,
            font_size,
            scale,
            screen_width,
            screen_height,
            color
        )
      )
    {
        position = init_position;
        this->screen_width = screen_width;
        this->screen_height = screen_height;
    }

    void setScreenSize(const unsigned int& new_screen_width, const unsigned int& new_screen_height) {
        screen_width = new_screen_width;
        screen_height = new_screen_height;
    }

    void update(float delta_time) {
        updateSprite(screen_width, screen_height);
    }
};