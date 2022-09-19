#pragma once

// STL includes
#include <iostream>
#include <string>
#include <vector>

namespace cl::lossless::other
{
class RunLengthCoding
{
public:
  const std::vector<std::string> encode(const std::vector<char>& symbols) const
  {
    return this->encode(symbols.begin(), symbols.end());
  }

  const std::vector<std::string> encode(auto begin, auto end) const
  {
    std::vector<std::string> result;
    if (begin >= end)
      return result;
    char previous_symbol = *begin;
    std::size_t c = 1;
    begin += 1;
    for (auto iter = begin; iter != end + 1; ++iter)
    {
      if (*iter != previous_symbol || iter == end)
      {
        result.push_back(std::to_string(c));
        result.push_back(std::string(1, previous_symbol));
        c = 0;
        previous_symbol = *iter;
      }
      ++c;
    }
    return result;
  }
};
} // namespace cl::lossless::other