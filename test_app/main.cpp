#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you
#include <cmath>
#include <filesystem>
#include <string>
#include <string_view>

// #include "app.h"
#include "engine.h"


int main() {
#ifdef __linux__
    std::filesystem::current_path(std::filesystem::canonical("/proc/self/exe").parent_path());
    printf("path: %s\n", std::filesystem::current_path().c_str());
#endif
    GF_Engine::Engine App(GF_Engine::Engine::create_window("My app", 800, 600), "My App");
    while(CLOSE_WINDOW(App.get_window())) { App.run(); }
    CLOSE_APP();
    return 0;
}
