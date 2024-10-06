#include <array>

#include <gtest/gtest.h>

#include <common/alphabets.hpp>
#include <lossless/other/move_to_front_transform.hpp>

using cl::lossless::other::MoveToFrontTransform;

TEST(MoveToFrontTransformTest, NoSymbols)
{
  const std::vector<char> symbols = {};
  MoveToFrontTransform mtft(cl::utils::alphabets::LOWER_CASE_ALPHABET);
  const MoveToFrontTransform::ResultType code_sequence = mtft.encode(symbols);
  EXPECT_EQ(symbols.size(), code_sequence.size());
}
TEST(MoveToFrontTransformTest, SymbolsSet1)
{
  const std::vector<char> symbols = {'b', 'a', 'n', 'a', 'n', 'a', 'a', 'a'};
  MoveToFrontTransform mtft(cl::utils::alphabets::LOWER_CASE_ALPHABET);
  const MoveToFrontTransform::ResultType code_sequence = mtft.encode(symbols);
  EXPECT_EQ(symbols.size(), code_sequence.size());
  EXPECT_EQ(1, code_sequence[0]);
  EXPECT_EQ(1, code_sequence[1]);
  EXPECT_EQ(13, code_sequence[2]);
  EXPECT_EQ(1, code_sequence[3]);
  EXPECT_EQ(1, code_sequence[4]);
  EXPECT_EQ(1, code_sequence[5]);
  EXPECT_EQ(0, code_sequence[6]);
  EXPECT_EQ(0, code_sequence[7]);
}
TEST(MoveToFrontTransformTest, SymbolsSet2)
{
  const std::vector<char> symbols = {'W', 'i', 'k', 'i', 'p', 'e', 'd', 'i', 'a'};
  MoveToFrontTransform mtft(cl::utils::alphabets::BYTE_ALPHABET);
  const MoveToFrontTransform::ResultType code_sequence = mtft.encode(symbols);
  EXPECT_EQ(symbols.size(), code_sequence.size());
  EXPECT_EQ(87, code_sequence[0]);
  EXPECT_EQ(105, code_sequence[1]);
  EXPECT_EQ(107, code_sequence[2]);
  EXPECT_EQ(1, code_sequence[3]);
  EXPECT_EQ(112, code_sequence[4]);
  EXPECT_EQ(104, code_sequence[5]);
  EXPECT_EQ(104, code_sequence[6]);
  EXPECT_EQ(3, code_sequence[7]);
  EXPECT_EQ(102, code_sequence[8]);
}