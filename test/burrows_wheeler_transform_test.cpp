#include <vector>

#include <gtest/gtest.h>

#include <coding_library/lossless/other/burrows_wheeler_transform.hpp>

using cl::lossless::other::BurrowsWheelerTransform;

TEST(BurrowsWheelerTransformTest, NoSymbols)
{
  const std::vector<char> symbols = {};
  BurrowsWheelerTransform bwt;
  const std::vector<char> code_sequence = bwt.Transform(symbols);
  EXPECT_EQ(symbols.size(), code_sequence.size());
}
TEST(BurrowsWheelerTransformTest, SymbolsSet1)
{
  const std::vector<char> symbols = {'B', 'A', 'N', 'A', 'N', 'A'};
  BurrowsWheelerTransform bwt;
  const std::vector<char> code_sequence = bwt.Transform(symbols);
  EXPECT_EQ(symbols.size() + BurrowsWheelerTransform::ADDITIONAL_SYMBOL_COUNT, code_sequence.size());
  EXPECT_EQ('B', code_sequence[0]);
  EXPECT_EQ('N', code_sequence[1]);
  EXPECT_EQ('N', code_sequence[2]);
  EXPECT_EQ('^', code_sequence[3]);
  EXPECT_EQ('A', code_sequence[4]);
  EXPECT_EQ('A', code_sequence[5]);
  EXPECT_EQ('|', code_sequence[6]);
  EXPECT_EQ('A', code_sequence[7]);
}