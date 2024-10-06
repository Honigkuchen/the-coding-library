#include <iostream>

#include <gtest/gtest.h>

#include <lossless/dictionary/lempel_ziv_77_coding.hpp>

using cl::lossless::dictionary::LempelZiv77Coding;

TEST(LempelZiv77CodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  LempelZiv77Coding lz77;
  const auto code_symbols = lz77.encode(symbols);
  EXPECT_EQ(0, code_symbols.size());
}
TEST(LempelZiv77CodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'b', 'a', 'b', 'c', 'b', 'a', 'b', 'a', 'b', 'a', 'a'};
  LempelZiv77Coding lz77;
  const auto code_symbols = lz77.encode(symbols);
  EXPECT_EQ(5, code_symbols.size());
  EXPECT_EQ(0, std::get<0>(code_symbols[0]));
  EXPECT_EQ(0, std::get<1>(code_symbols[0]));
  EXPECT_EQ('a', std::get<2>(code_symbols[0]));
  EXPECT_EQ(0, std::get<0>(code_symbols[1]));
  EXPECT_EQ(0, std::get<1>(code_symbols[1]));
  EXPECT_EQ('b', std::get<2>(code_symbols[1]));
  EXPECT_EQ(2, std::get<0>(code_symbols[2]));
  EXPECT_EQ(2, std::get<1>(code_symbols[2]));
  EXPECT_EQ('c', std::get<2>(code_symbols[2]));
  EXPECT_EQ(4, std::get<0>(code_symbols[3]));
  EXPECT_EQ(3, std::get<1>(code_symbols[3]));
  EXPECT_EQ('a', std::get<2>(code_symbols[3]));
  EXPECT_EQ(2, std::get<0>(code_symbols[4]));
  EXPECT_EQ(2, std::get<1>(code_symbols[4]));
  EXPECT_EQ('a', std::get<2>(code_symbols[4]));
}
