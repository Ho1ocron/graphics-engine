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


void MyApp::create_text(const char* text, const char* font_path, glm::vec3 position, float font_size, float scale, glm::vec3 color) {
    Text new_text(text, font_path, position, font_size, scale, SCR_WIDTH, SCR_HEIGHT,color);
    texts.push_back(new_text);
}


void MyApp::render_text() {
    for (Text& text : texts) {
        text.render();
    }
}


void MyApp::init() {
    create_window();
    setup();
}


void MyApp::run() {
    if (!window) init();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_text();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}


void MyApp::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    MyApp* app = static_cast<MyApp*>(glfwGetWindowUserPointer(window));
    if (!app) return;

    for (Text& text : app->texts) {
        text.setScreenSize(width, height);
    }
}


void MyApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}