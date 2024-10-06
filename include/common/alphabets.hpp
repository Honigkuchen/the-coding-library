#pragma once

// STL includes
#include <array>

// Project defines
#include "../defines.hpp"

namespace cl::utils::alphabets
{
CL_MAYBE_UNUSED static CL_CONSTEXPR std::array LOWER_CASE_ALPHABET{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                                                   'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                                                   's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
CL_MAYBE_UNUSED static CL_CONSTEXPR std::array LOWER_UPPER_ALPHABET{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                                                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                                                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A',
                                                                    'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                                                    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                                                                    'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

CL_NODISCARD CL_CONSTEXPR auto generate_ASCII_alphabet()
{
  CL_CONSTEXPR uint16_t kCharSizeAlphabet = 2 << (sizeof(char) * 8 - 1);
  std::array<char, kCharSizeAlphabet> alphabet = {};

  for (uint16_t i = 0; i < kCharSizeAlphabet; ++i)
    alphabet[i] = char(i);

  return alphabet;
}

static CL_CONSTEXPR std::array BYTE_ALPHABET = generate_ASCII_alphabet();
} // namespace cl::utils::alphabets