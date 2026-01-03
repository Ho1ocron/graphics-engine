#include "app.h"


int main() {
    MyApp app("Text Rendering", 800, 600);

    std::string regular_font = FONT_DIR REGULAR_FONT;
    std::string bold_font    = FONT_DIR BOLD_FONT;

    // initialize window and GL context before creating Text objects
    app.init();

    app.create_text(
        "Regular font text",
        regular_font.c_str(),
        glm::vec3{100.0f, 100.0f, 0.0f},
        48.0f,
        1.0f,
        glm::vec3{1.0f, 1.0f, 1.0f}
    );

    app.create_text(
        "Bold font text",
        bold_font.c_str(),
        glm::vec3{25.0f, 460.0f, 0.0f},
        48.0f,
        1.0f,
        glm::vec3{0.8f, 0.3f, 0.2f}
    );

    app.run();

    return 0;
}