#pragma once

// STL includes
#include <map>
#include <tuple>
#include <vector>

namespace cl::lossless::dictionary
{
class LempelZiv77Coding
{
public:
  [[nodiscard]] const std::pair<std::vector<char>, std::map<char, std::string>> encode(const std::vector<char>& symbols) const
  {
    std::vector<char> result;
    std::map<char, std::string> symbol_replace_table;
    if (symbols.empty())
      return std::make_pair(result, symbol_replace_table);
    result.insert(result.end(), symbols.begin(), symbols.end());

    // TODO

    return std::make_pair(result, symbol_replace_table);
  }
};
} // namespace cl::lossless::dictionary