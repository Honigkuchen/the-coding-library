#include <iostream>

#include <gtest/gtest.h>

#include <lossy/transform_type/DCT1.h>

class DCT1CodingTest : public ::testing::Test
{
};
TEST_F(DCT1CodingTest, NoSymbols)
{
  std::vector<double> numbers = {};
  cl::lossy::transform_type::DCT1 dct;
  const auto transformed_numbers = dct.transform(numbers);
  EXPECT_EQ(0, transformed_numbers.size());
}
TEST_F(DCT1CodingTest, NumbersTest1)
{
  const std::vector<int> numbers = {12, 24, 33, 0, 15};
  cl::lossy::transform_type::DCT1 dct;
  const auto transformed_numbers = dct.transform(numbers);
  EXPECT_EQ(5, transformed_numbers.size());
  EXPECT_EQ(57, transformed_numbers[0]);
  EXPECT_EQ(16, transformed_numbers[1]);
  EXPECT_EQ(-33, transformed_numbers[2]);
  EXPECT_EQ(-16, transformed_numbers[3]);
  EXPECT_EQ(9, transformed_numbers[4]);
}