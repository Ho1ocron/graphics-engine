#include "character_body_2d.h"

namespace GFE
{
    void CharacterBody2D::updateSprite(unsigned int width, unsigned int height)
    {
        sprite->update(1, width, height);
        sprite->move(position);
        sprite->draw();
    }

    void CharacterBody2D::move(float deltaTime, float screen_width, float screen_hight)
    {
        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;
        position.x = glm::clamp(position.x, 0.0f, screen_width);
        position.y = glm::clamp(position.y, 0.0f, screen_hight);
    }
}  // namespace GFE