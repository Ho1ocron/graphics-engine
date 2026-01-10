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
#include FT_FREETYPE_H


namespace GF_Engine {

    class Engine {
    private:
        int screen_width, screen_height;

        const char* window_name;
        const char* app_name;

        glm::vec3 bg_color;


        GLFWwindow* window;

    public:
        void init();
        void update();

        std::shared_ptr<Drawable2D> createObject(const Drawable2D& obj);
        void draw(std::shared_ptr<Drawable2D> obj);
        void deleteObject(std::shared_ptr<Drawable2D> obj) { obj.reset(); }

        void setBGColor(const glm::vec3& new_color);
        glm::vec3 getBGColor();

        Engine(const char* name, const int& screen_width, const int& screen_height, const glm::vec3& bg_color = {0.0f, 0.0f, 0.0f});
        ~Engine() = default;
    };

}  // namespace GF_Engine

#endif