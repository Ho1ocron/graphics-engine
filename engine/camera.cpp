#ifndef CAMERA_CPP
#define CAMERA_CPP

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>


class Camera {
    glm::vec2 _dimensions{1.0f, 1.0f};

public:
    glm::vec2 pos{};
    float zoom = 1.0f;
    // glm::mat4x4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

    glm::mat4x4 get_view_projection() const {
        glm::mat4x4 view{1.0f};
        view[3] = glm::vec4(pos, 0.0f, 1.0f);
        return glm::ortho(-_dimensions.x / 2.0f / zoom, _dimensions.x / 2.0f / zoom, -_dimensions.y / 2.0f / zoom, _dimensions.y / 2.0f / zoom, 0.0f, 1.0f) * view;
    }
    inline void set_dimensions(const uint w, const uint h) {
        _dimensions = {w, h};
        // projection = glm::ortho(-_dimensions.x / 2.0f, _dimensions.x / 2.0f, -_dimensions.y / 2.0f, _dimensions.y / 2.0f, 0.0f, 1.0f);
    }
    inline glm::vec2 get_dimensions() const { return _dimensions; }
};

#endif
