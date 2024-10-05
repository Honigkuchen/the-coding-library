#pragma once
#ifndef CL_LOG_HPP_
#define CL_LOG_HPP_

// STL includes
#ifdef CPP23
#include <print>
#endif

// Project includes
#include "../defines.hpp"

namespace CL::utils
{

template <typename T>
void print(const T& message)
{
#ifdef CPP23
#if __cpp_lib_print == 202207L
  std::print("{}\n", message);
#endif
#else
  std::cout << message << std::endl;
#endif
}
} // namespace CL::utils

#endif