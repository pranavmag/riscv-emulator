cmake_minimum_required(VERSION 3.20)
project(riscv_toolchain VERSION 1.0 LANGUAGES CXX)

# Enforce C++20 globally, no fallback
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force out-of-source builds — prevents polluting the source tree
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not allowed.\n"
        "Create a build directory and run cmake from there:\n"
        "  mkdir build && cd build && cmake ..")
endif()

add_subdirectory(shared)
add_subdirectory(emulator)
add_subdirectory(compiler)