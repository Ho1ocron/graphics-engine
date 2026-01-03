#include <stdio.h>
#include <iostream>

// #include "app.h"


void MyApp::do_something() {
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


int MyApp::create_window() {
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


void MyApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        printf("Key %d was pressed\n", key);
}


// void MyApp::load_font(const char* font_path) {FT_Library library;
//     // 1. Initialize the FreeType library
//     error = FT_Init_FreeType(&library);
//     if (error) {
//         std::cerr << "ERROR: Could not init FreeType library (Error code: " << error << ")" << std::endl;
//     }
//     // Check error codes for all FreeType functions

//     // 2. Load a font face from a file
//     // Replace "arial.ttf" with the path to your font file.
//     // The second argument (0) is the index of the font face in the file (most files have only one).
//     error = FT_New_Face(library, font_path, 0, &face);
//     if (error == FT_Err_Unknown_File_Format) {
//         std::cerr << "ERROR: Font format unsupported" << std::endl;
//     } else if (error) {
//         std::cerr << "ERROR: Could not open font file (Error code: " << error << ")" << std::endl;
//     }

//     // 3. Set the font size
//     // The size is specified in 1/64ths of a pixel, so 16*64 is 16 pixels.
//     // The 0s for the character width and height parameters indicate the size
//     // will be set relative to the pixel height.
//     error = FT_Set_Pixel_Sizes(face, 0, 16); // Set a font height of 16 pixels
//     if (error) {
//          std::cerr << "ERROR: Could not set pixel size (Error code: " << error << ")" << std::endl;
//     }
    
//     std::cout << "Font loaded successfully!" << std::endl;

//     error = FT_Load_Char(face, 'A', FT_LOAD_RENDER);
//     if (error) {
//         std::cerr << "ERROR: Could not load character 'A' (Error code: " << error << ")" << std::endl;
//     }
// }


struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Offset to advance to next glyph
};


// void MyApp::render_font() {
//     std::map<char, Character> Characters;
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//     for (unsigned char c = 0; c < 128; c++) {
//         // Load character glyph 
//         if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//             std::cerr << "ERROR: Failed to load Glyph for character " << c << std::endl;
//             continue;
//         }

//         unsigned int texture;
//         glGenTextures(1, &texture);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glTexImage2D(
//             GL_TEXTURE_2D,
//             0,
//             GL_RED,
//             face->glyph->bitmap.width,
//             face->glyph->bitmap.rows,
//             0,
//             GL_RED,
//             GL_UNSIGNED_BYTE,
//             face->glyph->bitmap.buffer
//         );
//         // set texture options
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//         // now store character for later use
//         Character character = {
//             texture, 
//             glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//             glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//             face->glyph->advance.x
//         };
//         Characters.insert(std::pair<char, Character>(c, character));
//     }
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
//     FT_Done_Face(face);
//     FT_Done_FreeType(library);
// }


void MyApp::run() {
    create_window();
    // load_font("JetBrainsMono-Italic.ttf");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
        // render_font();
        glfwSetKeyCallback(window, key_callback);
    }
    glfwTerminate();
}
