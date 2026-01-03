#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "text.h"
#include "constants.h"

// settings
constexpr unsigned int SCR_WIDTH  = 800;
constexpr unsigned int SCR_HEIGHT = 600;

static Text* g_regularText = nullptr;
static Text* g_boldText = nullptr;

// callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // =========================
    // GLFW
    // =========================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Text Rendering (OOP)",
        nullptr,
        nullptr
    );

    if (!window) {
        printf(LOAD_WINDOW_ERROR_MSG);
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // =========================
    // GLAD
    // =========================
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf(INIT_GLAD_ERROR_MSG);
        return -1;
    }

    // =========================
    // OpenGL state
    // =========================
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // =========================
    // Text objects
    // =========================
    const char* regular_font = FONT_DIR REGULAR_FONT;
    const char* bold_font    = FONT_DIR BOLD_FONT;
    Text regularText(
        "Regular font text", 
        regular_font,
        glm::vec3{25.0f, 520.0f, 0.0f},
        1.0f,
        SCR_WIDTH,
        SCR_HEIGHT,
        glm::vec3{1.0f, 1.0f, 1.0f}
    );

    Text boldText(
        "Bold font text", 
        bold_font,
        glm::vec3{25.0f, 460.0f, 0.0f},
        1.0f,
        SCR_WIDTH,
        SCR_HEIGHT,
        glm::vec3{0.8f, 0.3f, 0.2f}
    );

 
    // in framebuffer_size_callback:
   

    // =========================
    // Render loop
    // =========================
    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        regularText.render();
        boldText.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// =========================
// Input
// =========================
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// =========================
// Resize callback
// =========================
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{   
    glViewport(0, 0, width, height);
    if (g_regularText) g_regularText->setScreenSize(width, height);
    if (g_boldText)    g_boldText->setScreenSize(width, height);
    glViewport(0, 0, width, height);
}