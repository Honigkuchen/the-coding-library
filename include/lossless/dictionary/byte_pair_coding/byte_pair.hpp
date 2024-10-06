#pragma once
#ifndef CL_BYTE_PAIR_HPP_
#define CL_BYTE_PAIR_HPP_

// STL includes
#include <cstdint>

// Project defines
#include "../../../defines.hpp"

namespace cl::lossless::dictionary
{
struct BytePair
{
  CL_CONSTEXPR BytePair() CL_NOEXCEPT = default;
  CL_EXPLICIT CL_CONSTEXPR BytePair(const unsigned char f, const unsigned char s) CL_NOEXCEPT : first(f), second(s) {}
  CL_EXPLICIT CL_CONSTEXPR BytePair(unsigned char&& f, unsigned char&& s) CL_NOEXCEPT : first(f), second(s) {}
  uint8_t first{0};
  uint8_t second{0};
};

CL_NODISCARD CL_CONSTEXPR bool operator==(const BytePair& lhs, const BytePair& rhs) noexcept
{
  return lhs.first == rhs.first && lhs.second == rhs.second;
}
} // namespace cl::lossless::dictionary

#endif