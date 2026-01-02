#include <stdio.h>

#include <vector3.h>
#include <vector2.h>

#include "app.h"


void MyClass::do_something() {
    mymath::Vector3 vec3d1{1.0, 2.0, 3.0};
    mymath::Vector3 vec3d2{5.0, 5.0, 6.0};

    mymath::Vector3 vec3d3 = vec3d1 + vec3d2;

    bool areEqual = (vec3d1 == vec3d2);
    bool areNotEqual = (vec3d2 != vec3d3);

    printf(areEqual ? "vec3d1 is equal to vec3d2\n\n" : "vec3d1 is not equal to vec2\n\n");
    printf(areNotEqual ? "vec3d2 is not equal to vec3\n\n" : "vec3d1 is equal to vec3\n\n");
    printf("Resulting Vector: (%f, %f, %f)\n\n", vec3d3.x, vec3d3.y, vec3d3.z);

    double vec3d3_length = vec3d3.length();
    printf("Length of vec3d3: %f\n\n", vec3d3_length);

    vec3d3.normalize();
    double normal_vec3d3_length = vec3d3.length();

    printf("Normalized Vector: (%f, %f, %f) with length %f\n\n", vec3d3.x, vec3d3.y, vec3d3.z, normal_vec3d3_length);

    mymath::Vector2 vec2d1{3.0, 4.0};
    double vec2d1_length = vec2d1.length();
    printf("Length of vec3d2d1: %f\n\n", vec2d1_length);

    mymath::Vector2 vec2d2{6.0, 8.0};
    mymath::Vector2 vec2d3 = vec2d1 + vec2d2;
    printf("Resulting mymath::Vector2: (%f, %f)\n\n", vec2d3.x, vec2d3.y);

    printf("Resulting mymath::Vector2 Length: %f\n\n", vec2d3.length());

    vec2d3.normalize();
    printf("Normalized mymath::Vector2: (%f, %f) with length %f\n\n", vec2d3.x, vec2d3.y, vec2d3.length());
}


int MyClass::create_window() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "My GLFW Window", 0, 0);

    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    return 0;
}


void MyClass::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        printf("Key %d was pressed\n", key);
}


void MyClass::run() {
    create_window();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
        glfwSetKeyCallback(window, key_callback);
    }
    glfwTerminate();
}