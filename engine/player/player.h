#pragma once

#include "character_body_2d.h"
#include "text.h"


class Player : protected CharacterBody2D
{
private:
    glm::vec3 size;
    unsigned int screen_width;
    unsigned int screen_height;

    // Text s;


public:
    Player(
        const char* text,
        const char* font_path,
        const glm::vec3& init_position,
        float fontSize,
        float scale,
        const glm::vec3& color,
        unsigned int screen_width,
        unsigned int screen_height
    )
    : CharacterBody2D(
        std::make_unique<Text>(
            text,
            font_path,
            init_position,
            fontSize,
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