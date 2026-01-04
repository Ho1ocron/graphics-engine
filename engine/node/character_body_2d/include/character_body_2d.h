#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <type_traits>
#include <memory>
#include <variant>

#include "collision_body.h"


template<typename Drawable>
struct CharacterBody2D : public CollisionBody
{
    protected:
    Drawable sprite;

public:
    CharacterBody2D(const Drawable& new_sprite) : sprite(new_sprite) {}
    void move();
};