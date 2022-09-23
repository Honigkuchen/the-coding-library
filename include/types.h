#pragma once

// C includes
#include <cstddef>
#include <cstdint>

namespace cl::types
{
static_assert(sizeof(std::byte) == sizeof(uint_least8_t));
// using Byte = std::byte;
using Byte = unsigned char;
}