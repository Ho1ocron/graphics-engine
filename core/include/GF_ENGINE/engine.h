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

#define CLOSE_WINDOW glfwWindowShouldClose
#define CLOSE_APP glfwTerminate


namespace GF_Engine {

    class Engine {
    private:
        int screen_width, screen_height;
        GLFWwindow* window;

    public:
        void init();
        void update();

        std::shared_ptr<Drawable2D> create_object(const Drawable& obj);
        void delete_object(const std::shadre_ptr<Drawable2D>& obj) { obj.reset(); }

        Engine();
        ~Engine() = default;
    };

}  // namespace GF_Engine