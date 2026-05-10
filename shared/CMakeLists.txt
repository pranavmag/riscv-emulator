# INTERFACE = header-only, nothing to compile yet.
# When you add shared IR structs later, just drop headers in shared/include/shared/
add_library(riscv_shared INTERFACE)

target_include_directories(riscv_shared INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)