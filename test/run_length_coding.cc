#include <iostream>

#include <gtest/gtest.h>

#include <lossless/other/run_length_coding.h>

class RunLengthCodingTest : public ::testing::Test
{
};

TEST_F(RunLengthCodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  cl::lossless::other::RunLengthCoding rlc;
  std::vector<std::string> code_symbols = rlc.encode(symbols);
  EXPECT_EQ(0, code_symbols.size());
}
TEST_F(RunLengthCodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'a', 'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  cl::lossless::other::RunLengthCoding rlc;
  std::vector<std::string> code_symbols = rlc.encode(symbols);
  EXPECT_EQ(6, code_symbols.size());
  EXPECT_EQ("4", code_symbols[0]);
  EXPECT_EQ("a", code_symbols[1]);
  EXPECT_EQ("2", code_symbols[2]);
  EXPECT_EQ("b", code_symbols[3]);
  EXPECT_EQ("3", code_symbols[4]);
  EXPECT_EQ("c", code_symbols[5]);
}
