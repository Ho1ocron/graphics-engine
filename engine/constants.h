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
#endif
