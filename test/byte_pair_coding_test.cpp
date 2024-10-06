#include <iostream>

#include <gtest/gtest.h>

#include <lossless/dictionary/byte_pair_coding.hpp>

using cl::lossless::dictionary::BytePairCoding;

TEST(BytePairCodingTest, NoSymbols)
{
  using InputSymbolType = unsigned char;
  using OutputSymbolType = unsigned char;
  std::vector<InputSymbolType> symbols = {};
  BytePairCoding bpc;
  constexpr auto symbol_replacement_generator = []() -> OutputSymbolType
  {
    static OutputSymbolType symbol_A_offset = 0;
    if (symbol_A_offset == 26)
      throw std::runtime_error("Cannot generate more symbols for byte pair encoding");
    const OutputSymbolType symbol = 'Z' - symbol_A_offset;
    symbol_A_offset += 1;
    return symbol;
  };
  const auto code_symbols = bpc.encode<InputSymbolType, OutputSymbolType>(symbols, symbol_replacement_generator);
  EXPECT_EQ(0, code_symbols.first.size());
  EXPECT_EQ(0, code_symbols.second.size());
}
TEST(BytePairCodingTest, SymbolsSet1)
{
  using InputSymbolType = unsigned char;
  using OutputSymbolType = unsigned char;
  std::vector<InputSymbolType> symbols = {'a', 'a', 'a', 'b', 'd', 'a', 'a', 'a', 'b', 'a', 'c'};
  BytePairCoding bpc;
  constexpr auto symbol_replacement_generator = []() -> OutputSymbolType
  {
    static OutputSymbolType symbol_A_offset = 0;
    if (symbol_A_offset == 26)
      throw std::runtime_error("Cannot generate more symbols for byte pair encoding");
    const OutputSymbolType symbol = 'Z' - symbol_A_offset;
    symbol_A_offset += 1;
    return symbol;
  };
  const auto code_symbols = bpc.encode<InputSymbolType, OutputSymbolType>(symbols, symbol_replacement_generator);
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
  EXPECT_EQ('a', code_symbols.second.at('Z').first);
  EXPECT_EQ('a', code_symbols.second.at('Z').second);
  EXPECT_EQ('Z', code_symbols.second.at('Y').first);
  EXPECT_EQ('a', code_symbols.second.at('Y').second);
  EXPECT_EQ('Y', code_symbols.second.at('X').first);
  EXPECT_EQ('b', code_symbols.second.at('X').second);
}
