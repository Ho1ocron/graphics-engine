#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <type_traits>
#include <memory>
#include <variant>

#include "collision_body.h"
#include "drawable2d.h"
#include "collision_shape_2d.h"


// template<class Drawable2D>
struct CharacterBody2D : public CollisionBody
{
protected:
    std::unique_ptr<Drawable2D> sprite;
    std::unique_ptr<CircleCollisionShape2D> hitbox;

public:
    explicit CharacterBody2D(std::unique_ptr<Drawable2D> new_sprite) : sprite(std::move(new_sprite)) {}

    void move(float deltaTime, float screen_width, float screen_hight);

    void updateSprite(unsigned int width, unsigned int height);
};