set(EXECUTABLE_NAME Huffman_Encoding_Fast)
add_executable(${EXECUTABLE_NAME} main.cpp)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic)