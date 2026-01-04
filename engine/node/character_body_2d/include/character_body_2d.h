#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <type_traits>
#include <memory>
#include <variant>

#include "collision_body.h"


template<typename T>
struct CharacterBody2D : public CollisionBody
{
protected:
    T texture;

public:
    CharacterBody2D(
        const glm::vec3& position = {0.0f, 0.0f, 0.0f},
        const glm::vec3& velocity = {0.0f, 0.0f, 0.0f},
        const float& speed = 0.0f,
        const glm::vec3& acceleration = {0.0f, 0.0f, 0.0f},
        const glm::vec3& size,
        const T& texture,
        const glm::vec3& direction = glm::vec3(0.0f)
    ) : CollisionBody(position, direction, velocity, speed, acceleration, size), texture(texture) {}

    void update(float time_delta);
};