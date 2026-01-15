# GF Engine (gf-engine)
A simple game engine we are developing. It is based on *GLFW*, *OpenGL* framework, alongside with *GLM* for all the math and *Glad* for more functional. We also use *freetype* to render the text.

## Installation 
1. Clone the repository.
    ```bash
    git clone https://github.com/Ho1ocron/gf-engine.git
    ```
2. Init submodules (libraries that we use).
    ```bash
    git submodule update --init --recursive
    ```

## Usage

### Compile the engine.
We use *CMake* to help us compile the project.

1. Add our engine as a library in your app's `CMakeLists.txt`.
    ```CMake
    target_include_directories(engine)
    ```
2. Run:
    ```bash
    cmake --build --preset debug
    ```