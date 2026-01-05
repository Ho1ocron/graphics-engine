#ifndef RESOURCE_MANAGER_CPP
#define RESOURCE_MANAGER_CPP
#include <shader.h>

#include <map>
#include <memory>
#include <tuple>

#include "font.cpp"
#include "shader_paths.hpp"

inline constexpr decltype(std::ignore) preload{};

class ResourceManager {
public:
    using ShaderKey = ShaderID;
    using FontKey = std::pair<const char*, const unsigned int>;

private:
    std::map<ShaderKey, std::shared_ptr<Shader> > shaders;
    std::map<FontKey, std::shared_ptr<FontAtlas> > fonts;

public:
    template <ShaderKey key>
    std::shared_ptr<Shader> get_shader() {
        auto& ptr = shaders[key];
        constexpr ShadersPaths paths = ShadersPaths::get_path<key>();
        printf("path: %s\n", paths.vertex);
        printf("path: %s\n", paths.fragment);
        if(!ptr) ptr = std::make_shared<Shader>(paths.vertex, paths.fragment, paths.geometry);
        return ptr;
    }
    [[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
    std::shared_ptr<FontAtlas> get_font(const char* name, const unsigned int size = 12) {
        // path+extra slash+name+\0
        const size_t&& dir_len = strlen(FONT_DIR);
        const size_t&& name_len = strlen(name);
        char* path = new char[strlen(FONT_DIR) + name_len + 2]();
        memcpy(path, FONT_DIR, dir_len);
        memcpy(path + dir_len, "/", 1);
        memcpy(path + dir_len + 1, name, name_len);
        path[dir_len + name_len + 1] = '\0';

        auto& ptr = fonts[{path, size}];
        if(!ptr) ptr = std::make_shared<FontAtlas>(path, size);
        delete[] path;
        return ptr;
    }
};
#endif
