#pragma once

// STL includes
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace cl::lossless::dictionary
{
/**
 * \brief This class performs the encoding on symbols using the Byte-Pair-Coding algorithm.
 * \author Jonas 'Honigkuchen' Haubold
 * \date 2022
 * \copyright GNU Public License
 */
class BytePairCoding
{
public:
/**
 * @brief Encodes a collection of given symbols using the 'Byte-Pair-Coding' algorithm.
 * 
 * @param symbols The symbols to be encoded
 * @return const std::pair<std::vector<char>, std::map<char, std::string>> The resulting encoded collection of symbols
 */
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
        pos->second += 1;
    }

    std::sort(frequencies.begin(), frequencies.end(), [](auto& left, auto& right)
              {
                return left.second > right.second;
              });
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
} // namespace cl::lossless::dictionary