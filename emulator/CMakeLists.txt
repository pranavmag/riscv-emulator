add_executable(emulator
    src/main.cpp
    src/decoder.cpp
    src/decoder.h
    src/interpreter.cpp
    src/interpreter.h
)

target_include_directories(emulator PRIVATE src)

target_link_libraries(emulator PRIVATE riscv_shared)

# Warnings — treat your code seriously
target_compile_options(emulator PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)