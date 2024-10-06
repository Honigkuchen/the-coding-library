#pragma once
#ifndef RUN_LENGTH_CODING_IMPL_CPP20_HPP_
#define RUN_LENGTH_CODING_IMPL_CPP20_HPP_

#if !defined(CL_CPP20)
#error "Can't use the C++20 implementation for run length coding."
#else

// STL includes
#include <concepts>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

// Project includes
#include "../../../defines.hpp"

// Project includes
#include "run_length_coding_impl.hpp"

namespace cl::lossless::other::detail
{
template <typename T>
CL_CONCEPT Symbol = std::equality_comparable<T> && std::is_default_constructible_v<T>;

template <Symbol T>
class RunLengthCodingImplCpp20 : public detail::RunLengthCodingImpl<T>
{
};
} // namespace cl::lossless::other::detail
#endif
#endif