#include <iostream>

#include <gtest/gtest.h>

#include <lossless/other/run_length_coding/run_length_coding.hpp>

using cl::lossless::other::RunLengthCoding;

TEST(RunLengthCodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  RunLengthCoding<char> rlc;
  RunLengthCoding<char>::ResultType code_symbols = rlc.Encode(symbols);
  EXPECT_EQ(0, code_symbols.size());
}
TEST(RunLengthCodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'a', 'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  RunLengthCoding<char> rlc;
  RunLengthCoding<char>::ResultType code_symbols = rlc.Encode(symbols);
  EXPECT_EQ(3, code_symbols.size());
  EXPECT_EQ(4, code_symbols[0].count);
  EXPECT_EQ('a', code_symbols[0].symbol);
  EXPECT_EQ(2, code_symbols[1].count);
  EXPECT_EQ('b', code_symbols[1].symbol);
  EXPECT_EQ(3, code_symbols[2].count);
  EXPECT_EQ('c', code_symbols[2].symbol);
}
