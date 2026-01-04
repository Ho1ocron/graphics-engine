#pragma once

#include "character_body_2d.h"
#include "text.h"


class Player : protected CharacterBody2D<Text*>
{
private:
    Text* texture;
    glm::vec3 size;

public:
    Player(
        const glm::vec3& position = {0.0f, 0.0f, 0.0f},
        const glm::vec3& velocity = {0.0f, 0.0f, 0.0f},
        const float& speed = 0.0f,
        const glm::vec3& acceleration = {0.0f, 0.0f, 0.0f},
        const glm::vec3& direction = glm::vec3(0.0f)
    ) :size({1.0f, 1.0f, 1.0f}), CharacterBody2D(position, velocity, speed, acceleration, size, texture, direction) {}
};