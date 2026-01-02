# Graphics Engine

A small, personal graphics engine written in C++ — a place to experiment with math utilities and GLFW-based rendering.

---

## 🔧 Prerequisites

- **macOS** (instructions use macOS terminal) — works on Linux/Windows with equivalent tooling.
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

The project contains GLFW as a git submodule. Clone and initialize submodules before building:

```bash
git clone --recursive <repo-url> graphics-engine
cd graphics-engine
# If you already cloned without --recursive:
# git submodule update --init --recursive
```

---

## 🛠️ Build

From the project root (recommended out-of-source build):

```bash
# Create and enter a build directory
mkdir -p build && cd build

# Configure the project (default generator will be used; set -G "Ninja" to use Ninja)
cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release

# Build (use parallel jobs)
cmake --build . --config Release -- -j$(sysctl -n hw.ncpu)
```

If you prefer Ninja:

```bash
cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

The resulting executable will be at `build/graphics-engine`.

---

## ▶️ Run

From project root:

```bash
./build/graphics-engine
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
