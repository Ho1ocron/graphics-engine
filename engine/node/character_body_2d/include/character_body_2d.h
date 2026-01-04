#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <type_traits>
#include <memory>
#include <variant>

#include "collision_body.h"
#include "text.h"

template<typename T>
struct CharacterBody2D : public CollisionBody
{
private:
    T texture;

public:
    CharacterBody2D(
        const glm::vec3& position,
        const glm::vec3& velocity,
        const float& speed,
        const glm::vec3& acceleration,
        const glm::vec3& size,
        const T& texture,
        const glm::vec3& direction = glm::vec3(0.0f)
    ) : CollisionBody(position, direction, velocity, speed, acceleration, size), texture(texture) {}

    void update(float time_delta);
};