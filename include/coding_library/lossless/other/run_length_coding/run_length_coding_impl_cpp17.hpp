#pragma once
#ifndef RUN_LENGTH_CODING_IMPL_CPP17_HPP_
#define RUN_LENGTH_CODING_IMPL_CPP17_HPP_

#if !defined(CL_CPP17)
#error "Can't use the C++17 implementation for run length coding."
#else

// Project includes
#include "../../../defines.hpp"

// Project includes
#include "run_length_coding_impl.hpp"

namespace cl::lossless::other::detail
{
template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
class RunLengthCodingImplCpp17 : public detail::RunLengthCodingImpl<T>
{
};
} // namespace cl::lossless::other::detail

#endif
#endif