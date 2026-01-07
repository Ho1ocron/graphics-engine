#ifndef ENGINE
#define ENGINE

#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you

#include <camera.h>
#include <ft2build.h>
#include <label.h>
#include <resource_manager.h>

#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include FT_FREETYPE_H


template <class T>
struct DrawableContainer {
    using StaticResources = typename T::StaticResources;

    std::vector<std::unique_ptr<T>> objects;
    StaticResources draw_resources;

    void draw(const glm::mat4x4& VP) {
        draw_resources.use();
        for(const auto& obj : objects) { obj->draw(draw_resources, VP); }
    }

    // if StaticResources(ResourceManager&) exists, you may use
    // DrawableContainer(resource_manager)
    DrawableContainer(StaticResources res) : draw_resources(res) {}
};

namespace GF_Engine {
    class Engine {
    private:
        Camera camera{};

        float deltaTime = 0.0f;
        float timeNow = 0.0f;
        float lastFrame = 0.0f;

        ResourceManager resource_manager{"core/assets/shaders/", "assets/fonts/"};

    public:
        static GLFWwindow* create_window(const char* title, const unsigned int w, const unsigned int h) {
            glfwInit();
            GLFWwindow* out;
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHintString(GLFW_X11_CLASS_NAME, "graphics-engine");
            glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "graphics-engine");

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
            // clang-format off
            out = glfwCreateWindow(
                w,
                h,
                title,
                nullptr,
                nullptr
            );
            // clang-format on

            if(!out) printf(LOAD_WINDOW_ERROR_MSG);

            return out;
        }

        Engine(GLFWwindow*&& window, const char* app_title) {}

        float get_delta() const { return deltaTime; }
        float get_time() const { return timeNow; }

        Label& push_label(std::unique_ptr<Label>&& obj);
        Label& emplace_label(const char* text, const char* font_name, const Label::Alignment alignment = Label::Alignment::LEFT,
                             const glm::vec2& pos = {0.0, 0.0}, const float& height = 36, const glm::vec3& color = {1.0, 1.0, 1.0});
    };
}  // namespace GF_Engine
#endif