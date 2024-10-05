#pragma once

// C includes
#include <cstddef>
#include <cstdint>
#include <sstream>

namespace cl::types
{
static_assert(sizeof(std::byte) == sizeof(uint_least8_t));
using Byte = unsigned char;
/*!
 * \brief ToString This function converts a byte in binary representation to it's specific std::string representation.
 *
 * \param b The byte to print
 */
CL_NODISCARD std::string ToString(const Byte& b)
{
  std::stringstream ss;
  for (uint8_t i = 7; i != 0; --i)
  {
    const uint8_t mask = 1 << i;
    if ((b & mask) != 0)
      ss << "1";
    else
      ss << "0";
  }
  return ss.str();
}
}