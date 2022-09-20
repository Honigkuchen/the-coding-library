#include <iostream>

#include <gtest/gtest.h>

#include <lossless/other/byte_pair_coding.h>

class BytePairCodingTest : public ::testing::Test
{
};

TEST_F(BytePairCodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  cl::lossless::other::BytePairCoding bpc;
  const auto code_symbols = bpc.encode(symbols);
  EXPECT_EQ(0, code_symbols.first.size());
  EXPECT_EQ(0, code_symbols.second.size());
}
TEST_F(BytePairCodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'a', 'a', 'b', 'd', 'a', 'a', 'a', 'b', 'a', 'c'};
  cl::lossless::other::BytePairCoding bpc;
  const auto code_symbols = bpc.encode(symbols);
  EXPECT_EQ(3, code_symbols.second.size());
  EXPECT_EQ(5, code_symbols.first.size());
  EXPECT_EQ('X', code_symbols.first[0]);
  EXPECT_EQ('d', code_symbols.first[1]);
  EXPECT_EQ('X', code_symbols.first[2]);
  EXPECT_EQ('a', code_symbols.first[3]);
  EXPECT_EQ('c', code_symbols.first[4]);
  EXPECT_TRUE(code_symbols.second.find('Z') != code_symbols.second.end());
  EXPECT_TRUE(code_symbols.second.find('Y') != code_symbols.second.end());
  EXPECT_TRUE(code_symbols.second.find('X') != code_symbols.second.end());
  EXPECT_EQ("aa", code_symbols.second.at('Z'));
  EXPECT_EQ("Za", code_symbols.second.at('Y'));
  EXPECT_EQ("Yb", code_symbols.second.at('X'));
}
