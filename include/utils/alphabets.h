#pragma once

// STL includes
#include <array>

namespace cl::utils::alphabets
{
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
} // namespace cl::utils::alphabets