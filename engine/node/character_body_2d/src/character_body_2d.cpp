#include "character_body_2d.h"


void CharacterBody2D::updateSprite(unsigned int width, unsigned int height) {
    sprite->update(position, width, height);
    sprite->render();
}