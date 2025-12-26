# ascii-art Project

**scii-art** — a lightweight C++ demo app for ascii.

---

## 📋 Prerequisites

- **Operating System**: macOS (arm64)
- **Compiler**: g++ or clang with C++17 support
- **Build System**: CMake ≥ 3.30
- **Tools**:
  - `make` to build the project
  - `git` to clone the repository

---

## 📚 Required Libraries

- **Standard C++ Library (std)** — core language support
- **OpenCV** — image processing and computer vision
- **Boost** — utility libraries (filesystem, program options, etc.)
- **GoogleTest (gtest)** — unit testing framework

---

## 🚀 How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/saktanorovich/ascii-art.git
   cd ascii-art
2. **Build the project**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ctest
   cd ../
3. **Run the application**
   ```bash
   ./bin/ascii -h
   ./bin/ascii -i ./testsdata/00.jpg
