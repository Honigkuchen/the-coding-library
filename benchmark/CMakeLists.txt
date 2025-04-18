find_package(benchmark REQUIRED)
add_executable(${PROJECT_NAME}_benchmark benchmark.cpp run_length_coding.cpp
                                         byte_pair_coding.cpp)
target_include_directories(${PROJECT_NAME}_benchmark
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_benchmark benchmark::benchmark
                      benchmark::benchmark_main)
target_compile_options(${PROJECT_NAME}_benchmark
                       PRIVATE -Wall -Wextra -Wpedantic -Werror -Wconversion)
