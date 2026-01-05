#ifndef FONT_CPP
#define FONT_CPP
#include <array>
#include <cstddef>
#include <cstring>
#include <memory>

#include "app.h"
#include "constants.h"
#include "freetype/freetype.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_int2.hpp"
#include "texture.cpp"

struct Character {
    // unsigned int TextureID;
    unsigned int Advance;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    glm::vec2 TopLeft;
    glm::vec2 BottomRight;
};

// TODO: ignore first unprintable characters
// TODO: add languages
constexpr size_t NUM_CHARACTERS = 128;

class FontAtlas {
    // std::map<char, Character> _characters;
    std::array<Character, NUM_CHARACTERS> _characters;
    Texture _texture;


    // not in constructor because of Texture(const Texture&) = delete;
    Texture init_atlas(const char* path, const unsigned int& height) {
        FT_Library ft;
        if(const auto err = FT_Init_FreeType(&ft)) {
            printf("TODO: log library INIT (%d)\n", err);
            // TODO: LOGERRRET macro
            return Texture(0, 0, 0);
        }
        FT_Face face;
        if(const auto err = FT_New_Face(ft, path, 0, &face)) {
            printf("TODO: log library FACE (%d) %s\n", err, path);
            return Texture(0, 0, 0);
        }
        FT_Set_Pixel_Sizes(face, 0, height);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        unsigned int w = 0, h = 0;
        for(unsigned char c = 0; c < NUM_CHARACTERS; c++ /* :0 */) {
            if(FT_Load_Char(face, static_cast<char>(c), FT_LOAD_RENDER)) {
                printf("ERROR::FREETYPE: FT_Load_Char(i = %u) != 0\n", c);
                continue;
            }
            w += face->glyph->bitmap.width;
            h = std::max(h, face->glyph->bitmap.rows);
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (int)w, (int)h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);


        printf("ATLAS W: %u H: %u\n", w, h);
        unsigned long x = 0;
        for(unsigned char c = 0; c < NUM_CHARACTERS; c++ /* d:D */) {
            if(FT_Load_Char(face, static_cast<char>(c), FT_LOAD_RENDER)) {
                printf("ERROR::FREETYPE: FT_Load_Char(i = %u) != 0\n", c);
                continue;
            }
            const unsigned int& cw = face->glyph->bitmap.width;
            const unsigned int& ch = face->glyph->bitmap.rows;
            glTexSubImage2D(GL_TEXTURE_2D, 0, (int)x, 0, (int)cw, (int)ch, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            Character character;
            character.Size = {cw, ch};
            character.Bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
            character.Advance = face->glyph->advance.x;
            character.TopLeft = {float(x) / float(w), 0.0f};
            character.BottomRight = {float(x + cw) / float(w), float(ch) / float(h)};
            _characters[c] = character;

            x += cw;
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        return Texture(texture, w, h);
    }

public:
    FontAtlas(const char* path, const unsigned int& height) : _texture(init_atlas(path, height)) {}
    const Texture& get_texture() const { return _texture; }
    const Character& get_char(const char value) const {
        if(value > _characters.size())
            return _characters['?'];
        else
            return _characters[value];
    }
    void use() const { _texture.use(TextureUnits::FONT_ATLAS); }
};

class Label {
    std::shared_ptr<FontAtlas> _font;
    GLuint _VBO, _EBO, _VAO;
    unsigned int _len;

public:
    struct CharVertex {
        glm::vec2 pos = {0.0, 0.0};
        glm::vec2 origin = {0.0, 0.0};
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
    // fill VBO
    void set_text(const char* buf, const size_t& len) {
        SingleCharacter* vertices = new SingleCharacter[len]();
        GLuint* indices = new GLuint[len * INDICES_COUNT]();
        unsigned int x_px = 0;
        for(unsigned int i = 0; i < len; i++) {
            printf("i: %u x: %u\n", i, x_px);
            SingleCharacter& c_data = vertices[i];
            const auto& c_font = _font->get_char(buf[i]);

            // clang-format off
            c_data.top_left.pos     = {0.0, 0.0};
            c_data.top_right.pos    = {1.0, 0.0};
            c_data.bottom_left.pos  = {0.0, 1.0};
            c_data.bottom_right.pos = {1.0, 1.0};

            const float&& w = float(_font->get_texture().w());
            const float&& h = float(_font->get_texture().h());
            c_data.top_left.pos     = {float(x_px)/w, float(c_font.Size.y)/w};
            c_data.top_right.pos    = {float(x_px+c_font.Size.x)/w, float(c_font.Size.y)/w};
            c_data.bottom_left.pos  = {float(x_px)/w, 0.0};
            c_data.bottom_right.pos = {float(x_px+c_font.Size.x)/w, 0.0};
            // clang-format on

            c_data.top_left.tex_pos = {c_font.TopLeft.x, c_font.TopLeft.y};
            c_data.top_right.tex_pos = {c_font.BottomRight.x, c_font.TopLeft.y};
            c_data.bottom_left.tex_pos = {c_font.TopLeft.x, c_font.BottomRight.y};
            c_data.bottom_right.tex_pos = {c_font.BottomRight.x, c_font.BottomRight.y};

            x_px += c_font.Size.x;
        }
        for(unsigned int i = 0, v = 0; i < INDICES_COUNT * len; i += INDICES_COUNT, v += VERTICES_COUNT) {
            indices[i + 0] = v + 0;
            indices[i + 1] = v + 1;
            indices[i + 2] = v + 2;
            indices[i + 3] = v + 1;
            indices[i + 4] = v + 3;
            indices[i + 5] = v + 2;
        }

        glBindVertexArray(_VAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SingleCharacter) * len, vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * len * INDICES_COUNT, indices, GL_STATIC_DRAW);

        _len = len;

        glBindVertexArray(0);
        delete[] vertices;
        delete[] indices;
    }
    glm::vec3 color{1.0, 1.0, 1.0};
    Label(const std::shared_ptr<FontAtlas>& font, const glm::vec3& color, const char* buf = nullptr, const size_t len = 0) : color(color), _font(font) {
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
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex), (void*)offsetof(CharVertex, origin));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CharVertex), (void*)offsetof(CharVertex, tex_pos));

        if(buf) {
            if(len)
                set_text(buf, len);
            else
                set_text(buf, strlen(buf));
        }

        glBindVertexArray(0);
    }
    // TODO: static drawable resources
    void draw() const {
        _font->use();
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _len * INDICES_COUNT, GL_UNSIGNED_INT, 0);
        // glDrawElements(GL_LINE_LOOP, _len * INDICES_COUNT, GL_UNSIGNED_INT, 0);
    }
};
#endif
