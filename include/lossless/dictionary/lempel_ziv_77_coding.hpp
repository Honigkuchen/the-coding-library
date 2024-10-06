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
  [[nodiscard]] const std::vector<std::tuple<std::size_t, std::size_t, char>> encode(const std::vector<char>& symbols) const
  {
    std::vector<std::tuple<std::size_t, std::size_t, char>> triplets;
    if (symbols.empty())
      return triplets;

    constexpr unsigned int SIZE_LOOK_AHEAD_BUFFER = 4;
    constexpr unsigned int SIZE_SEARCH_BUFFER = 6;

    bool end_reached = false;

    auto index_is_valid = [&symbols](auto i)
    {
      return i < symbols.size();
    };

    for (std::size_t i = 0; i < symbols.size();)
    {
      std::string current = "";
      for (unsigned int j = 0; j != SIZE_LOOK_AHEAD_BUFFER; ++j)
      {
        if (!index_is_valid(i + j))
        {
          end_reached = true;
          break;
        }
        current.push_back(symbols[i + j]);
      }

      std::string current_search_buffer;
      for (unsigned int j = 0; j != SIZE_SEARCH_BUFFER; ++j)
        if (index_is_valid(i - SIZE_SEARCH_BUFFER + j))
          current_search_buffer.push_back(symbols[i - SIZE_SEARCH_BUFFER + j]);

      std::size_t o = 0; // How many steps to go back to find the start of the matching string
      std::size_t l = 0; // Length of the match
      char c = ' ';

      bool match_found = false;
      for (unsigned int j = 0; j != SIZE_LOOK_AHEAD_BUFFER - 1; ++j)
      {
        if (j != 0)
          current.erase(current.size() - 1);
        if (const auto index = current_search_buffer.rfind(current); index != std::string::npos)
        {
          match_found = true;
          const std::size_t pos = current_search_buffer.size() - index;
          o = pos;
          l = current.size();

          if (const std::size_t index = i + l; index_is_valid(index))
            c = symbols[index];
          else
            end_reached = true;
          break;
        }
        else
          continue;
      }
      if (!match_found)
        c = symbols[i];

      triplets.emplace_back(o, l, c);
      if (end_reached)
        i = symbols.size();
      else
        i += l + 1;
    }

    return triplets;
  }
};
} // namespace cl::lossless::dictionary