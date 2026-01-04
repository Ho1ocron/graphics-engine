#pragma once

#include "character_body_2d.h"
#include "text.h"


class Player : protected CharacterBody2D<Text*>
{
private:
    glm::vec3 size;
    unsigned int screen_width;
    unsigned int screen_height;

public:
    Player(
        const glm::vec3& init_position = {0.0f, 0.0f, 0.0f},
        const glm::vec3& velocity = {0.0f, 0.0f, 0.0f},
        const float& speed = 0.0f,
        const glm::vec3& acceleration = {0.0f, 0.0f, 0.0f},
        const glm::vec3& direction = glm::vec3(0.0f),
        const glm::vec3& size
    ) : CharacterBody2D(sprite) {}

    void setScreenSize(const unsigned int& new_screen_width, const unsigned int& new_screen_height) {
        screen_width = new_screen_width;
        screen_height = new_screen_height;
    }

    void update(float delta_time) {
        sprite->update(position, screen_width, screen_height);
    }
};