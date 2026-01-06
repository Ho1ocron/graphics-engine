#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you
#include <cmath>
#include <string>
#include <string_view>

#include "app.h"
#include "constants.h"


int main() {
    glfwInit();
    GLFWwindow *&&window = MyApp::create_window("[LOADING] Text Rendering", 800, 600);
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
           {-250, 50},
           48,
           {1.0, 1.0, 1.0}
    );
    Label &label2 = app.emplace_label("Bold font text",
           BOLD_FONT,
           {-250, -50},
           48,
           {0.8, 0.3, 0.2}
    );
    // printf("%p %p\n", label1.get(), label2.get());
    Label &label3 = app.emplace_label("Italic font text",
           ITALIC_FONT,
           {-250, -150},
           48,
           {0.8, 0.3, 0.2}
    );
    // clang-format on
    constexpr auto height = 16;
    constexpr size_t count = 160;
    constexpr glm::vec2 origin = {-50.0, 0.0};
    for(size_t i = 0; i < count; i++) {
        app.emplace_label("aghsfdjkghfjkadshjklf", REGULAR_FONT, origin + glm::vec2(0, height * (int(i) - int(count / 2))), height);
    }


    label2.set_text("Modified bold text!");
    label1.set_text("Modified regular text!").set_pos({-300, 50}).set_color({0, 1, 0});

    app.run([&]() {
        ;
        label2.set_text("{" + std::to_string(app.get_time()) + "}");
    });

    return 0;
}
