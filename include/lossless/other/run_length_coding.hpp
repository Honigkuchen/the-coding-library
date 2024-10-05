#pragma once

// STL includes
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

// Project includes
#include "../../defines.hpp"

namespace cl::lossless::other
{
#ifdef CL_CPP20
#include <concepts>
template <typename T>
CL_CONCEPT Symbol = std::equality_comparable<T> && std::is_default_constructible_v<T>;
template <Symbol T>
#elif defined(CL_CPP17)
template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
#endif
class RunLengthCoding
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

  CL_NODISCARD const ResultType encode(const std::vector<SymbolType>& symbols) const
  {
    return this->encode(symbols.begin(), symbols.end());
  }

  template <typename Iter>
  const ResultType encode(Iter begin, Iter end) const
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
} // namespace cl::lossless::other