# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(the-coding-library main_test.cc huffman_coding.cc run_length_coding.cc move_to_front_transform.cc burrows_wheeler_transform.cc)
target_link_libraries(the-coding-library GTest::gtest_main)
# add_test(NAME unit_test COMMAND unit_test)
include(GoogleTest)
gtest_discover_tests(the-coding-library)
