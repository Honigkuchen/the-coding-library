#pragma once

// STL includes
#include <deque>
#include <iterator>
#include <vector>

namespace cl::lossless::other
{
class MoveToFrontTransform
{
public:
  using DictionaryType = std::deque<char>;
  using ResultType = std::vector<DictionaryType::difference_type>;

private:
  DictionaryType dictionary;

public:
  template <typename C>
  explicit MoveToFrontTransform(const C& dictionary)
  {
    this->dictionary.assign(dictionary.begin(), dictionary.end());
  }
  CL_NODISCARD const std::vector<DictionaryType::difference_type> Encode(const std::vector<char>& symbols) const
  {
    std::deque<char> dictionary_copy = dictionary;
    std::vector<DictionaryType::difference_type> result;
    result.reserve(symbols.size());

    for (const char& s : symbols)
      if (const auto symbol_position = std::find(dictionary_copy.begin(), dictionary_copy.end(), s); symbol_position != dictionary_copy.end())
      {
        const std::deque<char>::difference_type rank =
            std::distance(dictionary_copy.begin(), symbol_position);
        result.push_back(rank);
        dictionary_copy.erase(symbol_position);
        dictionary_copy.push_front(s);
      }
    result.shrink_to_fit();
    return result;
  }
};
} // namespace cl::lossless::other