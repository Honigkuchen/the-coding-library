set(EXECUTABLE_NAME Huffman_Encoding)
add_executable(${EXECUTABLE_NAME} main.cc)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic)

# add_subdirectory(fast)