#pragma once

// STL includes
#include <algorithm>
#include <vector>

namespace cl::lossless::other
{
  /**
   * \brief This class performs the forward-transformation of the so called Buttows-Wheeler-Transform.
   * \author Jonas 'Honigkuchen' Haubold
   * \date 2022
   * \copyright GNU Public License
   */
class BurrowsWheelerTransform
{
public:
/**
 * @brief This static member indicates the number of extra symbols added to the encoded stream for decoding purpose.
 */
  static constexpr unsigned int ADDITIONAL_SYMBOL_COUNT = 2;
public:
/**
 * @brief Transforms a collection of given symbols using the 'Burrows-Wheeler-Transform' algorithm.
 * 
 * @details The algorithm transforms a collection of symbols in a way that repeating symbols or symbol groups are put next to each other so that e.g.
 * a byte-pair-coding or some other algorithm can use this to improve it's efficiency.
 * 
 * @param symbols The symbols to be transformed
 * @return const std::vector<char> The resulting transformed collection of symbols
 * 
 * @author Jonas 'Honigkuchen' Haubold
 * @see BytePairCoding
 */
  [[nodiscard]] const std::vector<char> transform(const std::vector<char>& symbols) const
  {
    std::vector<char> result;
    if (symbols.empty())
      return result;

    std::vector<char> symbols_appended;
    symbols_appended.emplace_back('^');
    symbols_appended.emplace_back('|');
    symbols_appended.insert(std::prev(symbols_appended.end()), symbols.begin(), symbols.end());

    std::vector<std::vector<char>>
        table;
    table.emplace_back(symbols_appended);
    for (std::size_t i = 0; i < symbols_appended.size() - 1; ++i)
    {
      std::vector<char> symbols_copy(symbols_appended.size());
      std::rotate_copy(symbols_appended.begin(), symbols_appended.end() - (i + 1), symbols_appended.end(), symbols_copy.begin());
      table.push_back(symbols_copy);
    }
    for (std::size_t i = 0; i < symbols_appended.size(); ++i)
    {
      std::sort(table.begin(), table.end(), [&i](const std::vector<char>& left, const std::vector<char>& right)
                {
                  if (left.size() != right.size())
                    throw std::runtime_error("String do not have equal size!");
                  for (std::size_t j = 0; j < i; ++j)
                    if (left[j] > right[j])
                      return false;
                  return left[i] < right[i];
                });
    }
    for (const auto& e : table)
      result.push_back(e.back());
    return result;
  }
};
} // namespace cl::lossless::other