#include "app.h"


void MyApp::create_window() {
 
}


void MyApp::setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Text Rendering (OOP)",
        nullptr,
        nullptr
    );

    if (!window) {
        printf(LOAD_WINDOW_ERROR_MSG);
        glfwTerminate();
        return;
    }

    // store this instance so static callbacks can access it
    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf(INIT_GLAD_ERROR_MSG);
        return;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


Text& MyApp::create_text(const char* text, const char* font_path, glm::vec3 position, float font_size, float scale, glm::vec3 color) {
    texts.emplace_back(std::make_unique<Text>(text, font_path, position, font_size, scale, SCR_WIDTH, SCR_HEIGHT, color));
    return *texts.back();
}


void MyApp::render_text() {
    for (const auto& text_ptr : texts) {
        if (text_ptr) text_ptr->render();
    }
}


void MyApp::modify_text(
    Text& text, const char* new_text, const char* new_font_path, 
    std::optional<glm::vec3> position,
    std::optional<float> font_size, std::optional<float> scale, 
    std::optional<glm::vec3> color
) {
    text.setText(new_text ? std::string(new_text) : text.getText());
}


void MyApp::init() {
    create_window();
    setup();
}


void MyApp::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    MyApp* app = static_cast<MyApp*>(glfwGetWindowUserPointer(window));
    if (!app) return;

    for (auto& text_ptr : app->texts) {
        if (text_ptr) text_ptr->setScreenSize(width, height);
    }
}


void MyApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (action == GLFW_PRESS || action == GLFW_REPEAT) 
        printf("Key %d pressed\n", key);
}


void MyApp::run(const std::function<void()>& on_update) {
    if (!window) init();

    while (!glfwWindowShouldClose(window)) {
        if (on_update) on_update();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_text();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}