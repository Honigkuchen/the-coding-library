#include <iostream>

#include <gtest/gtest.h>

#include <lossless/dictionary/byte_pair_coding.h>

class BytePairCodingTest : public ::testing::Test
{
};

TEST_F(BytePairCodingTest, NoSymbols)
{
  std::vector<char> symbols = {};
  cl::lossless::dictionary::BytePairCoding bpc;
  constexpr auto symbol_replacement_generator = []()
  {
    static unsigned int symbol_A_offset = 0;
    if (symbol_A_offset == 26)
      throw std::runtime_error("Cannot generate more symbols for byte pair encoding");
    const auto symbol = 'Z' - symbol_A_offset;
    symbol_A_offset += 1;
    return symbol;
  };
  const auto code_symbols = bpc.encode<char, char>(symbols, symbol_replacement_generator);
  EXPECT_EQ(0, code_symbols.first.size());
  EXPECT_EQ(0, code_symbols.second.size());
}
TEST_F(BytePairCodingTest, SymbolsSet1)
{
  std::vector<char> symbols = {'a', 'a', 'a', 'b', 'd', 'a', 'a', 'a', 'b', 'a', 'c'};
  cl::lossless::dictionary::BytePairCoding bpc;
  constexpr auto symbol_replacement_generator = []()
  {
    static unsigned int symbol_A_offset = 0;
    if (symbol_A_offset == 26)
      throw std::runtime_error("Cannot generate more symbols for byte pair encoding");
    const auto symbol = 'Z' - symbol_A_offset;
    symbol_A_offset += 1;
    return symbol;
  };
  const auto code_symbols = bpc.encode<char, char>(symbols, symbol_replacement_generator);
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
  EXPECT_EQ('a', code_symbols.second.at('Z')[0]);
  EXPECT_EQ('a', code_symbols.second.at('Z')[1]);
  EXPECT_EQ('Z', code_symbols.second.at('Y')[0]);
  EXPECT_EQ('a', code_symbols.second.at('Y')[1]);
  EXPECT_EQ('Y', code_symbols.second.at('X')[0]);
  EXPECT_EQ('b', code_symbols.second.at('X')[1]);
}
