#pragma once
#ifndef CL_TO_STRING_HPP_
#define CL_TO_STRING_HPP_

// STL includes
#include <string>

// Project defines
#include "../defines.hpp"

namespace cl
{
namespace detail
{
template <class... Ts>
std::string ToString(const Ts&...) = delete;
template <class T>
std::string ToStringImpl(T const& t)
{
  return ToString(t);
}
} // namespace detail
template <typename T>
CL_NODISCARD std::string ToString(const T& t)
{
  return detail::ToStringImpl(t);
}
} // namespace cl

#endif