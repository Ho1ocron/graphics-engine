#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <type_traits>
#include <memory>
#include <variant>

#include "collision_body.h"
#include "drawable2d.h"


// template<class Drawable2D>
struct CharacterBody2D : public CollisionBody
{
protected:
    std::unique_ptr<Drawable2D> sprite;

public:
    explicit CharacterBody2D(std::unique_ptr<Drawable2D> new_sprite) : sprite(std::move(new_sprite)) {}

    void move();

    void updateSprite(unsigned int w, unsigned int h) {
        sprite->update(position, w, h);
        sprite->render();
    }
};