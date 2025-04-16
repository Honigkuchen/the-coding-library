#pragma once

// STL includes
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

// Project defines
#include "../../../defines.hpp"

// Project includes
#include "byte_pair.hpp"

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
  template <typename S, typename T, typename U, typename = std::enable_if_t<std::is_unsigned_v<T>>>
  CL_NODISCARD const std::pair<std::vector<T>, std::map<T, BytePair>> Encode(const std::vector<S>& symbols, U replacement_symbol_generator) const
  {
    using SymbolType = S;
    using ReplacementSymbolType = T;

    std::vector<ReplacementSymbolType> result;
    std::map<ReplacementSymbolType, BytePair> symbol_replace_table;

    if (symbols.empty())
      return std::make_pair(result, symbol_replace_table);
    result.insert(result.end(), symbols.begin(), symbols.end());

    struct BytePairFrequencyType
    {
      CL_EXPLICIT CL_CONSTEXPR BytePairFrequencyType(BytePair&& b, uint64_t&& f) CL_NOEXCEPT : byte_pair(b), frequency(f) {}
      BytePair byte_pair;
      uint64_t frequency;
    };
    std::vector<BytePairFrequencyType> bytepair_frequencies;
    for (std::size_t i = 0; i < result.size() - 1; ++i)
    {
      BytePair s{result[i], result[i + 1]};
      const auto pos = std::find_if(bytepair_frequencies.begin(), bytepair_frequencies.end(), [&s](const BytePairFrequencyType& f)
                                    {
                                      return f.byte_pair == s;
                                    });
      if (pos == bytepair_frequencies.end())
        bytepair_frequencies.emplace_back(std::move(s), 1);
      else
        pos->frequency += 1;
    }
    std::sort(bytepair_frequencies.begin(), bytepair_frequencies.end(), [](const BytePairFrequencyType& left, const BytePairFrequencyType& right)
              {
                return left.frequency > right.frequency;
              });
    if (bytepair_frequencies.front().frequency > 1)
    {
      ReplacementSymbolType replace_symbol = replacement_symbol_generator();
      for (std::size_t i = 0; i < result.size() - 1; ++i)
      {
        const BytePair s{result[i], result[i + 1]};
        if (s == bytepair_frequencies.front().byte_pair)
        {
          symbol_replace_table[replace_symbol] = s;
          result[i] = replace_symbol;
          result.erase(result.begin() + static_cast<typename std::vector<ReplacementSymbolType>::difference_type>(i + 1));
        }
      }
      const auto recursive_result = Encode<SymbolType, ReplacementSymbolType>(result, replacement_symbol_generator);
      symbol_replace_table.insert(recursive_result.second.begin(), recursive_result.second.end());
      result = recursive_result.first;
    }
    return std::make_pair(result, symbol_replace_table);
  }
};
} // namespace cl::lossless::dictionary