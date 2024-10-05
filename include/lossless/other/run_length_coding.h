#pragma once

// STL includes
#include <concepts>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

namespace cl::lossless::other
{
template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
class RunLengthCoding
{
public:
  using SymbolType = T;
  struct SymbolRunLengthCoding
  {
    using CountType = uint64_t;
    SymbolType symbol;
    CountType count;
  };

  using ResultType = std::vector<SymbolRunLengthCoding>;

  [[nodiscard]] const ResultType encode(const std::vector<SymbolType>& symbols) const
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