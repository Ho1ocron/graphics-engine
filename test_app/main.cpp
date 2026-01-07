#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you
#include <cmath>
#include <filesystem>
#include <string>
#include <string_view>

#include "app.h"


int main() {
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif
    glfwInit();
    GLFWwindow*&& window = MyApp::create_window("[LOADING] Text Rendering", 800, 600);
    if(!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("!gladLoadGLLoader():%s\n", INIT_GLAD_ERROR_MSG);
        return 1;
    }

    MyApp app(std::move(window), "Text Rendering");


    // clang-format off
    Label &label1 = app.emplace_label("Regular font text",
           REGULAR_FONT,
           Label::Alignment::MIDDLE,
           {0, 50},
           48,
           {1.0, 1.0, 1.0}
    );
    Label &label2 = app.emplace_label("Bold font text",
           BOLD_FONT,
           Label::Alignment::MIDDLE,
           {0, 80-40-8},
           40,
           {0.8, 0.3, 0.2}
    );
    Label &label3 = app.emplace_label("Italic font text",
           ITALIC_FONT,
           Label::Alignment::MIDDLE,
           {0, -150},
           48,
           {0.8, 0.3, 0.2}
    );
    // clang-format on
    constexpr auto height = 16;
    constexpr size_t count = 160;
    constexpr glm::vec2 origin = {-50.0, 0.0};
    for(size_t i = 0; i < count; i++) {
        app.emplace_label("aghsfdjkghfjkadshjklf", REGULAR_FONT, Label::Alignment::LEFT, origin + glm::vec2(0, height * (int(i) - int(count / 2))), height);
    }
    app.emplace_label("!LEFT!", REGULAR_FONT, Label::Alignment::LEFT, {250.0, 0.0}).set_color({1.0, 1.0, 0.0});
    app.emplace_label("!RAIT!", REGULAR_FONT, Label::Alignment::RIGHT, {250.0, -36}).set_color({1.0, 1.0, 0.0});
    app.emplace_label("!MIDL!", REGULAR_FONT, Label::Alignment::MIDDLE, {250.0, 2 * -36}).set_color({1.0, 1.0, 0.0});


    label2.set_text("Modified bold text!");
    label1.set_text("Modified regular text!").set_pos({0, 80}).set_color({0, 1, 0});

    app.run([&]() {
        ;
        label2.set_text("{" + std::to_string(app.get_time()) + "}");
    });

    return 0;
}
