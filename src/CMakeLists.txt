find_package(fmt REQUIRED)

set(EXECUTABLE_NAME huffman_encoding)
add_executable(${EXECUTABLE_NAME} huffman_enoding.cpp)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wconversion -Wsign-conversion)
# add_subdirectory(fast)