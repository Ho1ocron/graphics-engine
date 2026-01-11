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


int main()
{
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif

    GF_Engine::Engine::print("Hello, World!");

    GF_Engine::Engine engine("My App", 800, 600);

    // engine.init();

    // while(engine.shouldQuit()) { engine.update(); }

    return 0;
}
