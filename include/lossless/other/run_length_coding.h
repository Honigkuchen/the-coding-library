#pragma once

// STL includes
#include <stack>
#include <string>
#include <vector>

namespace cl::lossless::other
{
class RunLengthCoding
{
public:
  const std::vector<char> encode(const std::vector<char>& symbols) const
  {
    return this->encode(symbols.begin(), symbols.end());
  }

  template <typename Iter>
  const std::vector<char> encode(Iter begin, Iter end) const
  {
    std::vector<char> result;
    if (begin >= end)
      return result;
    char previous_symbol = *begin;
    auto c = 1;
    begin += 1;
    for (auto iter = begin; iter != end + 1; ++iter)
    {
      if (*iter != previous_symbol || iter == end)
      {
        if (c > 0)
        {
          std::vector<char> tmp;
          while (c != 0)
          {
            const int last = c % 10;
            tmp.push_back(static_cast<char>('0' + last));
            c = (c - last) / 10;
          }
          std::reverse(tmp.begin(), tmp.end());
          result.insert(result.end(), tmp.begin(), tmp.end());
        }
        result.push_back(previous_symbol);
        c = 0;
        previous_symbol = *iter;
      }
      ++c;
    }
    return result;
  }
};
} // namespace cl::lossless::other