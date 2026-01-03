#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "collision_body.h"
#include "text.h"


struct CharacterBody2D : public CollisionBody, Text
{

};