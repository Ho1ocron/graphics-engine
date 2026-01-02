#include "app.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>


int main() {
    FT_Library library;
    FT_Face face;
    FT_Error error;

    // 1. Initialize the FreeType library
    error = FT_Init_FreeType(&library);
    if (error) {
        std::cerr << "ERROR: Could not init FreeType library (Error code: " << error << ")" << std::endl;
        return -1;
    }
    // Check error codes for all FreeType functions

    // 2. Load a font face from a file
    // Replace "arial.ttf" with the path to your font file.
    // The second argument (0) is the index of the font face in the file (most files have only one).
    error = FT_New_Face(library, "JetBrainsMono-Italic.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        std::cerr << "ERROR: Font format unsupported" << std::endl;
        return -1;
    } else if (error) {
        std::cerr << "ERROR: Could not open font file (Error code: " << error << ")" << std::endl;
        return -1;
    }

    // 3. Set the font size
    // The size is specified in 1/64ths of a pixel, so 16*64 is 16 pixels.
    // The 0s for the character width and height parameters indicate the size
    // will be set relative to the pixel height.
    error = FT_Set_Pixel_Sizes(face, 0, 16); // Set a font height of 16 pixels
    if (error) {
         std::cerr << "ERROR: Could not set pixel size (Error code: " << error << ")" << std::endl;
         return -1;
    }
    
    std::cout << "Font loaded successfully!" << std::endl;

    return 0;
}


// int main() {
//     MyClass obj;
//     // obj.doSomething();
//     obj.run();
//     return 0;
// }