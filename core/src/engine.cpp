#include "engine.h"


namespace GFE
{
    std::shared_ptr<Drawable2D> Engine::create_object(Drawable2D* obj)
    {
        std::shared_ptr<Drawable2D> ptr{obj};
        visible_on_screen.push_back(ptr);
        return ptr;
    }

    void Engine::draw(std::shared_ptr<Drawable2D> obj) { obj->draw(); }

    void Engine::draw_objs()
    {
        for(auto obj : visible_on_screen)
        {
            obj->draw();
            obj->update(deltaTime, screen_width, screen_height);
        }
    }

    void Engine::set_bg_color(const glm::vec4& new_color) { bg_color = new_color; }

    glm::vec4 Engine::get_bg_color() const { return bg_color; }

    void Engine::print(const char* str) { printf("%s\n", str); }

    Engine::Engine(const char* name, const int& screen_width, const int& screen_height, const glm::vec4& bg_color)
        : app_name(name), screen_height(screen_height), screen_width(screen_width), bg_color(bg_color)
    {
    }

    bool Engine::should_quit()
    {
        if(!window)
            return true;
        else
            return glfwWindowShouldClose(window);
    }


    void Engine::quit() { glfwTerminate(); }

    void Engine::init()
    {
        if(!glfwInit())
        {
            printf("Failed to initialize GLFW\n");
            return;  // make sure to exit or handle this case
        }
        // GLFWwindow* out;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHintString(GLFW_X11_CLASS_NAME, "graphics-engine");
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "graphics-engine");

#ifdef __APPLE__
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
        glfwInitHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
        window = glfwCreateWindow(screen_width, screen_height, app_name, nullptr, nullptr);
        if(!window)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
            glfwTerminate();
            return;
        }

        glfwGetFramebufferSize(window, &screen_width, &screen_height);
        glfwSetWindowUserPointer(window, this);
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


        camera.set_dimensions(screen_width, screen_height);

        glfwSetFramebufferSizeCallback(window,
                                       [](GLFWwindow* window, int w, int h)
                                       {
                                           glViewport(0, 0, w, h);
                                           Engine*&& app = static_cast<Engine*>(glfwGetWindowUserPointer(window));
                                           if(!app) return;
                                           app->camera.set_dimensions(w, h);
                                       });

        glViewport(0, 0, screen_width, screen_height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Engine::update()
    {
        timeNow = glfwGetTime();
        deltaTime = timeNow - lastFrame;
        lastFrame = timeNow;

        glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        const glm::mat4x4&& VP = camera.get_view_projection();

        draw_objs();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}  // namespace GFE
