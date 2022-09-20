#include <array>
#include <iostream>

#include <gtest/gtest.h>

#include <lossless/other/move_to_front_transform.h>

static constexpr auto LOWER_CASE_ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                             'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                             's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
static constexpr auto LOWER_UPPER_ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A',
                                              'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                              'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                                              'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

[[nodiscard]] constexpr auto generate_ASCII_alphabet()
{
  constexpr auto char_size_alphabet = 2 << (sizeof(char) * 8 - 1);
  std::array<char, char_size_alphabet> alphabet = {};

  for (auto i = 0; i < char_size_alphabet; ++i)
    alphabet[i] = char(i);

  return alphabet;
}

static constexpr auto BYTE_ALPHABET = generate_ASCII_alphabet();

class MoveToFrontTransformTest : public ::testing::Test
{
};

TEST_F(MoveToFrontTransformTest, NoSymbols)
{
  const std::vector<char> symbols = {};
  cl::lossless::other::MoveToFrontTransform mtft(LOWER_CASE_ALPHABET);
  const std::vector<unsigned int> code_sequence = mtft.encode(symbols);
  EXPECT_EQ(symbols.size(), code_sequence.size());
}
TEST_F(MoveToFrontTransformTest, SymbolsSet1)
{
  const std::vector<char> symbols = {'b', 'a', 'n', 'a', 'n', 'a', 'a', 'a'};
  cl::lossless::other::MoveToFrontTransform mtft(LOWER_CASE_ALPHABET);
  const std::vector<unsigned int> code_sequence = mtft.encode(symbols);
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
TEST_F(MoveToFrontTransformTest, SymbolsSet2)
{
  const std::vector<char> symbols = {'W', 'i', 'k', 'i', 'p', 'e', 'd', 'i', 'a'};
  cl::lossless::other::MoveToFrontTransform mtft(BYTE_ALPHABET);
  const std::vector<unsigned int> code_sequence = mtft.encode(symbols);
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