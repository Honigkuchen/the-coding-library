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
   * The output symbol type T must be able to represent the input symbol type S aswell as the generated output symbol types T, such that T completely contains S.
   *
   * @tparam S Input symbol type
   * @tparam T Output symbol type
   * @tparam U Generator function to create new output symbols of type T
   * @param symbols The symbols to be encoded
   * @param replacement_symbol_generator
   * @return const std::pair<std::vector<T>, std::map<T, std::vector<S>>> The resulting encoded collection of symbols
   */
  template <typename S, typename T, typename U>
  [[nodiscard]] const std::pair<std::vector<T>, std::map<T, std::vector<S>>> encode(const std::vector<S>& symbols, U replacement_symbol_generator) const
  {
    using SymbolType = S;
    using ReplacementSymbolType = T;

    std::vector<ReplacementSymbolType>
        result;
    std::map<ReplacementSymbolType, std::vector<SymbolType>> symbol_replace_table;

    if (symbols.empty())
      return std::make_pair(result, symbol_replace_table);
    result.insert(result.end(), symbols.begin(), symbols.end());
    std::vector<std::pair<std::vector<SymbolType>, unsigned int>> frequencies;
    for (std::size_t i = 0; i < result.size() - 1; ++i)
    {
      const std::vector<SymbolType> s{result[i], result[i + 1]};
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
      ReplacementSymbolType replace_symbol = replacement_symbol_generator();
      for (std::size_t i = 0; i < result.size() - 1; ++i)
      {
        const std::vector<SymbolType> s{result[i], result[i + 1]};
        if (s == frequencies.front().first)
        {
          symbol_replace_table[replace_symbol] = s;
          result[i] = replace_symbol;
          result.erase(result.begin() + i + 1);
        }
      }
      const auto recursive_result = encode<SymbolType, ReplacementSymbolType>(result, replacement_symbol_generator);
      symbol_replace_table.insert(recursive_result.second.begin(), recursive_result.second.end());
      result = recursive_result.first;
    }
    return std::make_pair(result, symbol_replace_table);
  }
};
} // namespace cl::lossless::dictionary