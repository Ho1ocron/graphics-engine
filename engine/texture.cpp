#ifndef TEXTURE_CPP
#define TEXTURE_CPP
#include <glad/glad.h>

#include "constants.h"

class Texture {
    unsigned int _id;
    unsigned int _w, _h;

public:
    // only get from ResourceManager
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    // TODO: loading texture from file
    // Texture(const char* path) {
    // static unsigned int count = 0;
    // int w, h, nchannels;
    // stbi_set_flip_vertically_on_load(true);
    // u_char* data = stbi_load(path, &w, &h, &nchannels, 0);
    // if (!data)
    //     LERR("failed to load texture ({}) {}: {}", count, path, stbi_failure_reason());
    // else {
    //     LTRACE("w{} h{} channels{} count{}", w, h, nchannels, count);
    //     glGenTextures(1, &_id);
    //     glBindTexture(GL_TEXTURE_2D, _id);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //     if (nchannels == 4)
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //     else
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //     // glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // stbi_image_free(data);
    // count++;
    // _w = w;
    // _h = h;
    // }

    // i guess its okay but doubt
    Texture(const unsigned int id, const unsigned int w, const unsigned int h) : _id(id), _w(w), _h(h) {}

    inline void use(const TextureUnits& texture_unit) const {
        glActiveTexture(GL_TEXTURE0 + static_cast<unsigned char>(texture_unit));
        glBindTexture(GL_TEXTURE_2D, _id);
    }
    inline unsigned int w() const { return _w; }
    inline unsigned int h() const { return _h; }
};
#endif
