set(PROJECT_TESTS_NAME "coding-library-tests")
add_executable(${PROJECT_TESTS_NAME}
  main_test.cc
  huffman_coding_test.cc
  run_length_coding_test.cc
  move_to_front_transform_test.cc
  burrows_wheeler_transform_test.cc
  byte_pair_coding_test.cc
  lempel_ziv_77_coding_test.cc
  DCT1_test.cc)
target_link_libraries(${PROJECT_TESTS_NAME} GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_TESTS_NAME})
