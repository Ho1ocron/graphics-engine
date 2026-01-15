#include <cmath>
#include <string>

#ifdef __linux__
#include <filesystem>
#endif
// #include "app.h"
#include <engine.h>
#include <text.h>

#include "player/player.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BG_COLOR {0.1f, 0.1f, 0.1f, 1.0f}
#define YELLOW {1.0f, 1.0f, 0.0f}
#define BLUE {0.0f, 1.0f, 1.0f}

#define CHARACTER "@*>"


GPE::Vec3 dynamic_gradient(float time)
{
    return GPE::Vec3{(sinf(time) + 1.0f) / 2.0f, (cosf(time) + 1.0f) / 2.0f, 0.5f};
}


int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    GPE::Engine::print_str("Hello, World!");

    GPE::Engine engine{"My App", SCREEN_WIDTH, SCREEN_HEIGHT, BG_COLOR};

    engine.init();

    // GPE::Text text1{"Hello, World!", "assets/fonts/JetBrainsMono-Regular.ttf", {25.0f, 50.0f,
    // 0.0f}, 52.0f, 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, YELLOW};

    std::shared_ptr<GPE::Text> text1 = engine.create_object<GPE::Text>(std::move(
        std::make_unique<GPE::Text>("Hello, World!", "assets/fonts/JetBrainsMono-Regular.ttf",
                                    GPE::Vec3{25.0f, 50.0f, 0.0f}, 52.0f, 0.5f, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, GPE::Vec3 YELLOW)));

    text1->setPositionOnScreenCenter();


    while(!engine.should_quit())
    {
        text1->setColor(dynamic_gradient(engine.get_time()));
        engine.update();
    }

    engine.quit();
    return 0;
}
