#ifndef RESOURCE_MANAGER_CPP
#define RESOURCE_MANAGER_CPP
#include <shader.h>

#include <cstdio>
#include <cstring>
#include "resource_manager.h"


[[nodiscard("Are you preloading resources? Use preload = get_font() then")]]
std::shared_ptr<FontAtlas> ResourceManager::get_font(const char* name, const unsigned int size) {
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


#endif
