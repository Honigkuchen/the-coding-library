# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(unit_test unit_test.cc)
target_link_libraries(unit_test gtest_main)
add_test(NAME unit_test COMMAND unit_test)
