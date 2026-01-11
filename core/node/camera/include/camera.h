#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace GFE
{
    class Camera
    {
        glm::vec2 _dimensions{1.0f, 1.0f};

    public:
        glm::vec2 pos{};
        float zoom = 1.0f;

        glm::mat4x4 get_view_projection() const;
        void set_dimensions(const uint w, const uint h);
        glm::vec2 get_dimensions() const;
    };
}  // namespace GFE