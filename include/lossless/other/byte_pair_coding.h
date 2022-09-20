#pragma once

// STL includes
#include <map>
#include <string>
#include <tuple>
#include <vector>

// Debug includes
#include <iostream>

namespace cl::lossless::other
{
class BytePairCoding
{
public:
  [[nodiscard]] const std::pair<std::vector<char>, std::map<char, std::string>> encode(const std::vector<char>& symbols) const
  {
    std::vector<char> result;
    std::map<char, std::string> symbol_replace_table;
    if (symbols.empty())
      return std::make_pair(result, symbol_replace_table);
    result.insert(result.end(), symbols.begin(), symbols.end());
    std::vector<std::pair<std::string, unsigned int>> frequencies;

    for (std::size_t i = 0; i < result.size() - 1; ++i)
    {
      const std::string s{result[i], result[i + 1]};
      const auto pos = std::find_if(frequencies.begin(), frequencies.end(), [&s](const auto& f)
                                    {
                                      return f.first == s;
                                    });
      if (pos == frequencies.end())
        frequencies.emplace_back(s, 1);
      else
        pos->second += 1; // Creates the entry in the table if it does not exist yet!
    }

    std::sort(frequencies.begin(), frequencies.end(), [](auto& left, auto& right)
              {
                return left.second > right.second;
              });
#if DEBUG
    auto print_frequencies = [&frequencies]()
    {
      for (const auto& [k, v] : frequencies)
        std::cout << k << ", " << v << '\n';
      std::cout << std::endl;
    };
    print_frequencies();
#endif
    if (frequencies.front().second > 1)
    {
      static unsigned int replace_symbol_offset = 0;
      for (std::size_t i = 0; i < result.size() - 1; ++i)
      {
        const std::string s{result[i], result[i + 1]};
        if (s == frequencies.front().first)
        {
          char replace_symbol = 'Z' - replace_symbol_offset; // Yes, we can only replace a limited amount of symbols. But good enough here...
          symbol_replace_table[replace_symbol] = s;
          result[i] = replace_symbol;
          result.erase(result.begin() + i + 1);
        }
      }
      replace_symbol_offset += 1;
      const std::pair<std::vector<char>, std::map<char, std::string>> recursive_result = encode(result);
      symbol_replace_table.insert(recursive_result.second.begin(), recursive_result.second.end());
      result = recursive_result.first;
    }
    return std::make_pair(result, symbol_replace_table);
  }
};
} // namespace cl::lossless::other