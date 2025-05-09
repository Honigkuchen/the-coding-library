set(PROJECT_TESTS_NAME "coding-library-tests")
find_package(GTest REQUIRED)
add_executable(
  ${PROJECT_TESTS_NAME}
  main_test.cpp
  huffman_coding_test.cpp
  run_length_coding_test.cpp
  move_to_front_transform_test.cpp
  burrows_wheeler_transform_test.cpp
  byte_pair_coding_test.cpp
  lempel_ziv_77_coding_test.cpp
  DCT1_test.cpp)
target_compile_options(
  ${PROJECT_TESTS_NAME} PUBLIC -Wall -Werror -Wextra -Wpedantic -Wconversion
                               -Wsign-conversion)
target_include_directories(${PROJECT_TESTS_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_TESTS_NAME} GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_TESTS_NAME})
