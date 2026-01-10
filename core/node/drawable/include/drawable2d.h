#pragma once

#include <glm/glm.hpp>


struct Drawable2D {
    virtual ~Drawable2D() = default;

    virtual void update(const glm::vec3& new_position, const unsigned int& screen_width, const unsigned int& screen_height) = 0;

    virtual void draw() = 0;

    virtual void free() = 0;
};