add_executable(the-coding-library
  main_test.cc
  huffman_coding.cc
  modified_huffman_coding.cc
  run_length_coding.cc
  move_to_front_transform.cc
  burrows_wheeler_transform.cc
  byte_pair_coding.cc
  lempel_ziv_77_coding.cc
  DCT1.cc)
target_link_libraries(the-coding-library GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(the-coding-library)
