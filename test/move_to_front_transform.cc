#include <iostream>

#include <gtest/gtest.h>

#include <lossless/other/move_to_front_transform.h>

static constexpr auto ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

class MoveToFrontTransformTest : public ::testing::Test
{
};

TEST_F(MoveToFrontTransformTest, NoSymbols)
{
  std::vector<char> symbols = {};
  cl::lossless::other::MoveToFrontTransform mtft(ALPHABET);
  std::vector<unsigned int> code_sequence = mtft.encode(symbols);
  EXPECT_EQ(0, code_sequence.size());
}
TEST_F(MoveToFrontTransformTest, SymbolsSet1)
{
  std::vector<char> symbols = {'b', 'a', 'n', 'a', 'n', 'a', 'a', 'a'};
  cl::lossless::other::MoveToFrontTransform mtft(ALPHABET);
  std::vector<unsigned int> code_sequence = mtft.encode(symbols);
  EXPECT_EQ(8, code_sequence.size());
  EXPECT_EQ(1, code_sequence[0]);
  EXPECT_EQ(1, code_sequence[1]);
  EXPECT_EQ(13, code_sequence[2]);
  EXPECT_EQ(1, code_sequence[3]);
  EXPECT_EQ(1, code_sequence[4]);
  EXPECT_EQ(1, code_sequence[5]);
  EXPECT_EQ(0, code_sequence[6]);
  EXPECT_EQ(0, code_sequence[7]);
}
