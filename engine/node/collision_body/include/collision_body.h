#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


struct CollisionBody
{
private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 velocity;
    float speed;
    glm::vec3 acceleration;
    glm::vec3 size;

public:
    CollisionBody(
        const glm::vec3& position,
        const glm::vec3& direction,
        const glm::vec3& velocity,
        const float& speed,
        const glm::vec3& acceleration,
        const glm::vec3& size
    ) : position(position), direction(direction), size(size), velocity(velocity), speed(speed), acceleration(acceleration) {}

    void setPosition(const glm::vec3& new_position);
    glm::vec3 getPosition() const;

    void setVelocity(const glm::vec3& new_velocity);
    glm::vec3 getVelocity() const;

    void setAcceleration(const glm::vec3& new_acceleration);
    glm::vec3 getAcceleration() const;

    void setSize(const glm::vec3& new_size);
    glm::vec3 getSize() const;

    void update(float delta_time);
};