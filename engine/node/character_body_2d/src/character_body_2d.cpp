#include "character_body_2d.h"


void CharacterBody2D::updateSprite(unsigned int width, unsigned int height) {
    sprite->update(position, width, height);
    sprite->render();
}


void CharacterBody2D::move(float deltaTime) {
    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
    // position.x = std::clamp(position.x, 1, 2);
}