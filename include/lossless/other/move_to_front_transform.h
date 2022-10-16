#pragma once

// STL includes
#include <deque>
#include <iterator>
#include <vector>

namespace cl::lossless::other
{
class MoveToFrontTransform
{
private:
  std::deque<char> dictionary;

public:
  template <typename C>
  explicit MoveToFrontTransform(const C& dictionary)
  {
    this->dictionary.assign(dictionary.begin(), dictionary.end());
  }
  [[nodiscard]] const std::vector<unsigned int>
  encode(const std::vector<char>& symbols) const
  {
    std::deque<char> dictionary_copy = dictionary;
    std::vector<unsigned int> result;
    result.reserve(symbols.size());

    for (const auto& s : symbols)
    {
      const auto symbol_position = std::find(dictionary_copy.begin(), dictionary_copy.end(), s);
      if (symbol_position != dictionary_copy.end())
      {
        const unsigned int rank =
            std::distance(dictionary_copy.begin(), symbol_position);
        result.push_back(rank);
        dictionary_copy.erase(symbol_position);
        dictionary_copy.push_front(s);
      }
    }
    result.shrink_to_fit();
    return result;
  }
};
} // namespace cl::lossless::other