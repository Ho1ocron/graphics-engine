#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <memory>
#include <string_view>
#include <utility>

#include "font.h"
#include "shader.h"
#include "shader_paths.hpp"

inline constexpr decltype(std::ignore) preload{};

class ResourceManager {
public:
    using ShaderKey = ShaderID;
    using FontKey = std::pair<std::string, const unsigned int>;

private:
    std::map<ShaderKey, std::shared_ptr<Shader> > shaders;
    std::map<FontKey, std::shared_ptr<FontAtlas> > fonts;

public:
    template <ShaderKey key>
    std::shared_ptr<Shader> get_shader() {
        auto& ptr = shaders[key];
        constexpr ShadersPaths paths = ShadersPaths::get_path<key>();
        if(!ptr) ptr = std::make_shared<Shader>(paths.vertex, paths.fragment, paths.geometry);
        return ptr;
    }
    [[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
    std::shared_ptr<FontAtlas> get_font(const std::string_view& name, const unsigned int size = 12);
};
#endif
