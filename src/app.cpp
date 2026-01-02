#include "app.h"
#include "vector3.h"
#include "vector2.h"

#include <stdio.h>


void MyClass::doSomething() {
    Vector3 vec3d1{1.0, 2.0, 3.0};
    Vector3 vec3d2{5.0, 5.0, 6.0};

    Vector3 vec3d3 = vec3d1 + vec3d2;

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

    Vector2 vec2d1{3.0, 4.0};
    double vec2d1_length = vec2d1.length();
    printf("Length of vec3d2d1: %f\n\n", vec2d1_length);

    Vector2 vec2d2{6.0, 8.0};
    Vector2 vec2d3 = vec2d1 + vec2d2;
    printf("Resulting Vector2: (%f, %f)\n\n", vec2d3.x, vec2d3.y);

    printf("Resulting Vector2 Length: %f\n\n", vec2d3.length());

    vec2d3.normalize();
    printf("Normalized Vector2: (%f, %f) with length %f\n\n", vec2d3.x, vec2d3.y, vec2d3.length());
}