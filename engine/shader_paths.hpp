enum class ShaderID { TEXT };

struct ShadersPaths {
    const char* vertex;
    const char* fragment;
    const char* geometry;
    constexpr ShadersPaths(const char* vertex, const char* fragment, const char* geometry = nullptr) : vertex(vertex), fragment(fragment), geometry(geometry) {}
    template <enum ShaderID>
    constexpr static const ShadersPaths get_path() {
        // default (unknown)
        return ShadersPaths{"text.vs", "text.fs", nullptr};
    }
};

// TODO: add SHADER_DIR "/" in ResourceManager
#define _SHADER2(ID, vertpath, fragpath)                                       \
    template <>                                                                \
    constexpr const ShadersPaths ShadersPaths::get_path<ShaderID::ID>() {      \
        return ShadersPaths{SHADER_DIR "/" vertpath, SHADER_DIR "/" fragpath}; \
    }
#define _SHADER3(ID, vertpath, fragpath, geompath)                                                      \
    template <>                                                                                         \
    constexpr const ShadersPaths ShadersPaths::get_path<ShaderID::ID>() {                               \
        return ShadersPaths{SHADER_DIR "/" vertpath, SHADER_DIR "/" fragpath, SHADER_DIR "/" geompath}; \
    }

#pragma region list_shaders
_SHADER2(TEXT, "text.vs", "text.fs")
#pragma endregion

#undef _SHADER2
#undef _SHADER3
