#ifndef LABEL_HPP
#define LABEL_HPP

#include <glm/ext/vector_float3.hpp>
#include <memory>

#include "font.h"
#include "resource_manager.h"
#include "shader.h"

class Label {
    std::shared_ptr<FontAtlas> _font;
    GLuint _VBO, _EBO, _VAO;
    unsigned int _len;

    glm::vec2 pos{};

    struct CharVertex {
        glm::vec2 pos = {0.0, 0.0};
        glm::vec2 tex_pos = {0.0, 0.0};
    };
    struct SingleCharacter {
        CharVertex top_left;      // 0
        CharVertex top_right;     // 1
        CharVertex bottom_left;   // 2
        CharVertex bottom_right;  // 3
    };
    constexpr static size_t VERTICES_COUNT = 4;
    constexpr static size_t INDICES_COUNT = 6;  // 6 indices for 4 vertices
private:
    glm::mat4x4 get_model() const ;

public:
    glm::vec3 color{1.0, 1.0, 1.0};

    struct StaticResources {
        const std::shared_ptr<Shader> shader;

    public:
        void use() const { shader->use(); }
        StaticResources(const std::shared_ptr<Shader>& shader) : shader(shader) {}
        StaticResources(ResourceManager& resource_manager) : shader(resource_manager.get_shader<ShaderID::TEXT>()) {}
    };

public:
    // refills VBO and EBO, so please do not use frequently
    void set_text(const char* buf, const size_t& len);

    void draw(const StaticResources& res, const glm::mat4x4 VP) const;
    Label(const std::shared_ptr<FontAtlas>& font, const glm::vec3& color, const glm::vec2& pos={0.0, 0.0}, const char* buf = nullptr, const size_t len = 0);
};

#endif
