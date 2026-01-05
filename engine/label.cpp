#ifndef LABEL_CPP
#define LABEL_CPP

#include "label.hpp"

#include <cstring>

// TODO: lazy buffers updating
void Label::set_text(const char* buf, const size_t& len) {
    // TODO: use the same buffer for all set_text() calls so there will be no allocs
    SingleCharacter* vertices = new SingleCharacter[len]();
    GLuint* indices = new GLuint[len * INDICES_COUNT]();

    unsigned int x_px = 0;
    // fill VBO
    for(unsigned int i = 0; i < len; i++) {
        SingleCharacter& c_data = vertices[i];
        const auto& c_font = _font->get_char(buf[i]);
        const float&& w = _font->get_texture().w();
        // const float&& h = _font->get_height();
        const float&& h = _font->get_texture().h();
        const float&& font_h = _font->get_height();

        // clang-format off
        c_data.top_left.pos         = {(x_px), (c_font.size.y)};
        c_data.top_left.tex_pos     = {c_font.top_left.x, c_font.top_left.y};
        c_data.top_right.pos        = {(x_px+c_font.size.x), (c_font.size.y)};
        c_data.top_right.tex_pos    = {c_font.bottom_right.x, c_font.top_left.y};
        c_data.bottom_left.pos      = {(x_px), 0.0};
        c_data.bottom_left.tex_pos  = {c_font.top_left.x, c_font.bottom_right.y};
        c_data.bottom_right.pos     = {(x_px+c_font.size.x), 0.0};
        c_data.bottom_right.tex_pos = {c_font.bottom_right.x, c_font.bottom_right.y};
        // clang-format on


        x_px += c_font.size.x;
    }
    // fill EBO
    for(unsigned int i = 0, v = 0; i < INDICES_COUNT * len; i += INDICES_COUNT, v += VERTICES_COUNT) {
        indices[i + 0] = v + 0;  // top_left
        indices[i + 1] = v + 1;  // top_right
        indices[i + 2] = v + 2;  // bottom_left
        indices[i + 3] = v + 1;  // top_right
        indices[i + 4] = v + 3;  // bottom_right
        indices[i + 5] = v + 2;  // bottom_left
    }

    glBindVertexArray(_VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SingleCharacter) * len, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * len * INDICES_COUNT, indices, GL_STATIC_DRAW);

    _len = len;

    glBindVertexArray(0);
    delete[] vertices;
    delete[] indices;
}

Label::Label(const std::shared_ptr<FontAtlas>& font, const glm::vec3& color, const glm::vec2& pos, const char* buf, const size_t len)
    : color(color), _font(font), pos(pos) {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex), (void*)offsetof(CharVertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex), (void*)offsetof(CharVertex, tex_pos));

    if(buf)
        set_text(buf, len ? len : strlen(buf));
    else
        glBindVertexArray(0);
}

void Label::draw(const StaticResources& res, const glm::mat4x4 VP) const {
    _font->use();
    res.shader->setMat4("MVP", VP * get_model());
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _len * INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

glm::mat4x4 Label::get_model() const {
    glm::mat4x4 out{1.0f};
    // set position
    out[3][0] = pos.x;
    out[3][1] = pos.y;
    out[3][2] = 0.0f;
    return out;
}

#endif
