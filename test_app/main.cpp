#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you
#include <cmath>
#include <string>
#include <string_view>

#ifdef __linux__
#include <filesystem>
#endif
// #include "app.h"
#include <engine.h>
#include <text.h>
// #include "player/player.h"

#define BG_COLOR {0.1f, 0.1f, 0.1f, 1.0f}


int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    GFE::Engine::print("Hello, World!");

    GFE::Engine engine("My App", 800, 600, BG_COLOR);

    engine.init();

    GFE::Text text1("text 1", "assets/fonts/JetBrainsMono-Regular.ttf", {25.0f, 50.0f, 0.0f}, 48.0f, 1.0f, 800, 600, {1.0f, 1.0f, 1.0f});
    std::shared_ptr<Drawable2D> text_obj1 = engine.create_object(&text1);

    while(!engine.should_quit()) { engine.update(); }

    engine.quit();
    return 0;
}
