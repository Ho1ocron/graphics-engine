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

#define CLOSE_WINDOW glfwWindowShouldClose
#define CLOSE_APP glfwTerminate

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
        GLFWwindow* window = nullptr;

        ResourceManager resource_manager{"core/assets/shaders/", "assets/fonts/"};

        float deltaTime = 0.0f;
        float timeNow = 0.0f;
        float lastFrame = 0.0f;

        const char* title;
        int SCR_WIDTH, SCR_HEIGHT;

    public:
        DrawableContainer<Label> labels;
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
        GLFWwindow* get_window() { return window; }

        Engine(GLFWwindow*&& window, const char* app_title)
            : window(window), title(app_title ? app_title : glfwGetWindowTitle(window)), labels(resource_manager) {
            glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
            camera.set_dimensions(SCR_WIDTH, SCR_HEIGHT);
            // store this instance so static callbacks can access it
            glfwSetWindowUserPointer(window, this);

            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
                glViewport(0, 0, w, h);
                Engine*&& app = static_cast<Engine*>(glfwGetWindowUserPointer(window));
                if(!app) return;
                app->camera.set_dimensions(w, h);
            });

            glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void set_background(glm::vec3 color);

        void run() {
            if(!window) printf("MyApp::window == nullptr\n");
            // Player player(SCR_WIDTH, SCR_HEIGHT, window, glm::vec3{100.0f, 200.0f, 0.0f});
            timeNow = glfwGetTime();
            deltaTime = timeNow - lastFrame;
            lastFrame = timeNow;

            // player.update(deltaTime);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            const glm::mat4x4&& VP = camera.get_view_projection();
            labels.draw(VP);

            glfwSwapBuffers(window);
            glfwPollEvents();

            // glfwTerminate();
        }

        float get_delta() const { return deltaTime; }
        float get_time() const { return timeNow; }

        Label& push_label(std::unique_ptr<Label>&& obj);
        Label& emplace_label(const char* text, const char* font_name, const Label::Alignment alignment = Label::Alignment::LEFT,
                             const glm::vec2& pos = {0.0, 0.0}, const float& height = 36, const glm::vec3& color = {1.0, 1.0, 1.0});
    };
}  // namespace GF_Engine
#endif