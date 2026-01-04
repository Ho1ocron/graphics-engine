# Graphics Engine

A small, personal graphics engine written in C++ — a place to experiment with math utilities and GLFW-based rendering.


## 🔧 Prerequisites

- **macOS** (instructions use macOS terminal) — should work on Linux/Windows with equivalent tooling.
- **CMake** (>= 3.14)
- **A C/C++ compiler** (Xcode Command Line Tools / clang / gcc)
- Optional: **Ninja** (recommended for faster builds)

Install common tools via Homebrew if needed:

```bash
# Install Homebrew first (if you don't have it):
# /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install cmake ninja
```

---

## ⚙️ Initialize the project

The project contains GLFW, GLM and Freetype as a git submodule. Clone and initialize submodules before building:

```bash
git clone --recursive https://github.com/Ho1ocron/graphics-engine.git
cd graphics-engine
# If you already cloned without --recursive:
# git submodule update --init --recursive
```


## 🛠️ Build and run

From the project root:

```bash
# Create a build directory
mkdir build

# Configure the project (see cmake --list-presets)
cmake --preset debug-ninja

# Build in parallel and run
cmake --build --preset debug -j$(sysctl -n hw.ncpu) && ./build/graphics-engine
```

If you want to run with a debugger or from an IDE, you can generate an Xcode project or other generator using CMake (e.g. `-G "Xcode"`).

---

## 🧭 Troubleshooting

- If CMake fails to find GLFW or build errors reference missing headers, ensure submodules were initialized: `git submodule update --init --recursive`.
- Install Xcode command-line tools if the compiler is missing: `xcode-select --install`.
- If CMake version is too old, update it via Homebrew.

---

## Contributing

Contributions welcome! Suggested workflow:

1. Fork the repo and create a branch for your feature/fix.
2. Add tests or small demos for new features when applicable.
3. Open a Pull Request with a clear description and any reproduction steps.

---

## License & Notes

This is a personal project for learning and experimentation.

If you want a quick start or help with a platform-specific issue, open an issue and include your OS, CMake version, and the failure output.
