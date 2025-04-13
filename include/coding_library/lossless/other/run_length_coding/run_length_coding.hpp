#pragma once
#ifndef RUN_LENGTH_CODING_HPP_
#define RUN_LENGTH_CODING_HPP_

// STL includes
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

// Project includes
#include "../../../defines.hpp"

// Project includes
#ifdef CL_CPP20
#include "run_length_coding_impl_cpp20.hpp"
#elif defined(CL_CPP17)
#include "run_length_coding_impl_cpp17.hpp"
#endif

namespace cl::lossless::other
{
#ifdef CL_CPP20
template <typename T>
using RunLengthCoding = detail::RunLengthCodingImplCpp20<T>;
#elif defined(CL_CPP17)
template <typename T>
using RunLengthCoding = detail::RunLengthCodingImplCpp17<T>;
#endif
} // namespace cl::lossless::other
#endif