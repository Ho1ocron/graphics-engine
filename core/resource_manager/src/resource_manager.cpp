#ifndef RESOURCE_MANAGER_CPP
#define RESOURCE_MANAGER_CPP
#include <resource_manager.h>
#include <shader.h>

#include <string>

[[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
std::shared_ptr<FontAtlas> ResourceManager::get_font(const std::string_view& name, const unsigned int size) {
    const std::string&& path = std::string(FONT_DIR) + '/' + name.data();
    std::shared_ptr<FontAtlas>& ptr = fonts[{path, size}];
    if(!ptr) ptr = std::make_shared<FontAtlas>(path.c_str(), size);
    return ptr;
}


#endif
