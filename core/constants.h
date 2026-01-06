#ifndef CONSTANTS_H
#define CONSTANTS_H
constexpr const char* REGULAR_FONT = "JetBrainsMono-Regular.ttf";
constexpr const char* BOLD_FONT = "JetBrainsMono-Bold.ttf";
constexpr const char* ITALIC_FONT = "JetBrainsMono-Italic.ttf";

constexpr const char* LOAD_FONT_ERROR_MSG = "ERROR::FREETYPE: Failed to load font";
constexpr const char* LOAD_FONT_NAME_ERROR_MSG = "ERROR::FREETYPE: Failed to load font_name";
constexpr const char* LOAD_GLYPH_ERROR_MSG = "ERROR::FREETYTPE: Failed to load Glyph";
constexpr const char* LOAD_WINDOW_ERROR_MSG = "Failed to create GLFW window";
constexpr const char* INIT_GLAD_ERROR_MSG = "Failed to initialize GLAD";
constexpr const char* INIT_FREETYPE_ERROR_MSG = "ERROR::FREETYPE: Could not init FreeType Library";

enum class TextureUnits : unsigned char {
    GENERAL0 = 0,
    GENERAL1 = 1,
    FONT_ATLAS = 3,
    TextureUnits_MAX = 16,
};

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

#endif
