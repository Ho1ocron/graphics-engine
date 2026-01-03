#include "app.h"
#include <cmath>


void update_text(Text& text) {
    float time = static_cast<float>(glfwGetTime());
    glm::vec3 pos = text.getPosition();
    pos.x = 100.0f + 60.0f * sinf(time);
    pos.y = 100.0f + 20.0f * sinf(time * 2.0f);
    text.setPosition(pos);
    text.setColor(glm::vec3{ (sinf(time) + 1.0f) / 2.0f, (cosf(time) + 1.0f) / 2.0f, 0.5f });

     // toggle text every second
    if (static_cast<int>(time)) 
        text.setText("Seconds: "+std::to_string(static_cast<int>(time)));
}


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


    app.run([&]() {update_text(text1); });

    return 0;
}