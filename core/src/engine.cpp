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

    void Engine::set_bg_color(const glm::vec3& new_color) { bg_color = new_color; }

    glm::vec3 Engine::get_bg_color() const { return bg_color; }

    void Engine::print(const char* str) { printf("%s\n", str); }

    Engine::Engine(const char* name, const int& screen_width, const int& screen_height, const glm::vec3& bg_color)
        : app_name(name), screen_height(screen_height), screen_width(screen_width), bg_color(bg_color)
    {
    }

    bool Engine::should_quit() { return true; }

    void Engine::init() {}

    void Engine::update()
    {
        for(auto obj : visible_on_screen)
        {
            obj->draw();
            obj->update(deltaTime, screen_width, screen_height);
        }
    }
}  // namespace GFE