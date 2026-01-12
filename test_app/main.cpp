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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BG_COLOR {0.1f, 0.1f, 0.1f, 1.0f}
#define YELLOW {1.0f, 1.0f, 0.0f}
#define BLUE {0.0f, 1.0f, 1.0f}

typedef struct
{
    int x;
    int y;
} MyStruct;


int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    GFE::Engine::print("Hello, World!");

    GFE::Engine engine("My App", SCREEN_WIDTH, SCREEN_HEIGHT, BG_COLOR);

    engine.init();

    MyStruct my_struct_1 = {0, 0};
    MyStruct my_struct_2 = {1, 1};

    printf("x: %d, y: %d\n", my_struct_1.x, my_struct_1.y);

    GFE::Text text1("Hello, World!", "assets/fonts/JetBrainsMono-Regular.ttf", {25.0f, 50.0f, 0.0f}, 48.0f, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, YELLOW);
    text1.getCenter();
    text1.setPositionOnScreenCenter();
    // text1.setPosition(engine.get_screen_center());
    std::shared_ptr<Drawable2D> text_obj1 = engine.create_object(&text1);

    while(!engine.should_quit()) { engine.update(); }

    engine.quit();
    return 0;
}
