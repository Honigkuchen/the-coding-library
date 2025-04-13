#pragma once
#ifndef RUN_LENGTH_CODING_IMPL_HPP_
#define RUN_LENGTH_CODING_IMPL_HPP_

// STL includes
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

// Project includes
#include "../../../defines.hpp"

namespace cl::lossless::other::detail
{
template <typename T>
class RunLengthCodingImpl
{
public:
  using SymbolType = T;
  struct SymbolRunLengthCoding
  {
    using CountType = uint64_t;

    CL_CONSTEXPR CL_EXPLICIT SymbolRunLengthCoding(const SymbolType& s, const CountType& c) CL_NOEXCEPT : symbol(s), count(c) {}

    SymbolType symbol;
    CountType count;
  };
  using ResultType = std::vector<SymbolRunLengthCoding>;

  CL_NODISCARD const ResultType Encode(const std::vector<SymbolType>& symbols) const
  {
    return this->Encode(symbols.begin(), symbols.end());
  }

  template <typename Iter>
  const ResultType Encode(Iter begin, Iter end) const
  {
    ResultType result;
    if (begin >= end)
      return result;
    SymbolType current_symbol = *begin;
    typename SymbolRunLengthCoding::CountType c = 1;
    begin += 1;
    for (auto iter = begin; iter != end + 1; ++iter)
    {
      if ((*iter != current_symbol || iter == end) && c > 0)
      {
        result.emplace_back(current_symbol, c);
        c = 0;
        current_symbol = *iter;
      }
      ++c;
    }
    return result;
  }
};
} // namespace cl::lossless::other::detail

#endif