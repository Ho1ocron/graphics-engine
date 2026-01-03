// #include "app.h"
// #include "constants.h"


// void MyApp::create_window() {
//     glfwInit();

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, nullptr, nullptr);
//     if (!window) {
//         printf(LOAD_WINDOW_ERROR_MSG);
//         glfwTerminate();
//         return;
//     }
// }


// void MyApp::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     // make sure the viewport matches the new window dimensions; note that width and 
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }


// int MyApp::run() {
//     create_window();
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         printf(INIT_GLAD_ERROR_MSG);
//         return -1;
//     }

//     // OpenGL state
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     // Shader
//     Shader shader(SHADER_DIR "text.vs", SHADER_DIR "text.fs");
//     glm::mat4 projection = glm::ortho(
//         0.0f,
//         static_cast<float>(SCR_WIDTH),
//         0.0f,
//         static_cast<float>(SCR_HEIGHT)
//     );

//     shader.use();
//     glUniformMatrix4fv(
//         glGetUniformLocation(shader.ID, "projection"),
//         1,
//         GL_FALSE,
//         glm::value_ptr(projection)
//     );

//     // =========================
//     // Load fonts
//     // =========================
//     const std::string regular_font_path = FONT_DIR REGULAR_FONT;
//     const std::string italic_font_path  = FONT_DIR ITALIC_FONT;
//     const std::string bold_font_path    = FONT_DIR BOLD_FONT;

//     Font regularFont = LoadFont(regular_font_path, 24);
//     Font italicFont  = LoadFont(italic_font_path, 24);
//     Font boldFont    = LoadFont(bold_font_path, 24);

//     // =========================
//     // VAO / VBO
//     // =========================
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(
//         0,
//         4,
//         GL_FLOAT,
//         GL_FALSE,
//         4 * sizeof(float),
//         (void*)0
//     );

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     // =========================
//     // Render loop
//     // =========================
//     glfwSwapInterval(0);
//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);

//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         RenderText(
//             shader, regularFont, "Regular font text",
//             25.0f, 500.0f, 1.0f,
//             glm::vec3(0.9f, 0.9f, 0.9f)
//         );

//         RenderText(
//             shader, boldFont, "Bold font text", 
//             25.0f, 460.0f, 1.0f, 
//             glm::vec3(0.7f, 0.8f, 1.0f)
//         );
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
    

//     glfwTerminate();
//     return 0;
// }