#include <iostream>

#include <gtest/gtest.h>

#include <lossless/dictionary/lempel_ziv_77_coding.h>

class LempelZiv77CodingTest : public ::testing::Test
{
};

TEST_F(LempelZiv77CodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  cl::lossless::dictionary::LempelZiv77Coding lz77;
  const auto code_symbols = lz77.encode(symbols);
  EXPECT_EQ(0, code_symbols.first.size());
  EXPECT_EQ(0, code_symbols.second.size());
}
TEST_F(LempelZiv77CodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'a', 'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  cl::lossless::dictionary::LempelZiv77Coding lz77;
  const auto code_symbols = lz77.encode(symbols);
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
