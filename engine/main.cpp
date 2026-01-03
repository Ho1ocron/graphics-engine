#include "app.h"
#include <cmath>


int main() {
    MyApp app("Text Rendering", 800, 600);

    std::string regular_font = FONT_DIR REGULAR_FONT;
    std::string bold_font    = FONT_DIR BOLD_FONT;
    
    app.init();

    Text& text1 = app.create_text(
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


    app.run([&]() {
        float t = static_cast<float>(glfwGetTime());

        glm::vec3 pos = text1.getPosition();
        pos.x = 100.0f + 60.0f * sinf(t);
        pos.y = 100.0f + 20.0f * sinf(t * 2.0f);
        text1.setPosition(pos);
        text1.setColor(glm::vec3{ (sinf(t) + 1.0f) / 2.0f, (cosf(t) + 1.0f) / 2.0f, 0.5f });

        // toggle text every second
        if (static_cast<int>(t) % 2 == 0) {
            text1.setText("Even second");
        } else {
            text1.setText("Odd second");
        }
    });

    return 0;
}