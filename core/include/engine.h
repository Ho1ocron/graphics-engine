#ifndef ENGINE
#define ENGINE

#include <glad/glad.h>
// hey clang-format please dont shuffle includes here
#include <GLFW/glfw3.h>
// thank you

#include <camera.h>
#include <drawable2d.h>
#include <ft2build.h>
#include <label.h>
#include <resource_manager.h>

#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include FT_FREETYPE_H


namespace GFE
{

    class Engine
    {
    private:
        int screen_width, screen_height;

        const char* window_name;
        const char* app_name;

        glm::vec3 bg_color;

        GLFWwindow* window;

        Camera camera{};

        float deltaTime = 0.0f;
        float timeNow = 0.0f;
        float lastFrame = 0.0f;

        std::vector<std::shared_ptr<Drawable2D>> visible_on_screen;
        std::vector<std::shared_ptr<Drawable2D>> hidden_on_screen;

    public:
        void init();
        void update();
        bool should_quit();

        std::shared_ptr<Drawable2D> create_object(Drawable2D* obj);
        void draw(std::shared_ptr<Drawable2D> obj);
        void delete_object(std::shared_ptr<Drawable2D> obj) { obj.reset(); }

        float get_deltaTime() const { return deltaTime; }
        float get_time() const { return timeNow; }

        void set_bg_color(const glm::vec3& new_color);
        glm::vec3 get_bg_color() const;

        static void print(const char* str);

        Engine(const char* name, const int& screen_width, const int& screen_height, const glm::vec3& bg_color = {0.0f, 0.0f, 0.0f});
        ~Engine() = default;
    };

}  // namespace GFE

#endif