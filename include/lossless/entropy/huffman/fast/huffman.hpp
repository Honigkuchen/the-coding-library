#pragma once

// C++ includes
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <type_traits>
#include <vector>

namespace huffman::fast
{
/*!
 * \brief TraverseTree This function creates the binary codes by traversing the Huffman graph.
 *
 * The traversal is done recursively. If the graph is too large (like really really large...) this may lead to a stack overflow, pay attention!
 *
 * \param node The current node to traverse from
 * \param prefix The current prefix to append the current and all child nodes to
 *
 * \return A map of symbols and their corresponding Huffman binary representation
 */
#if 0
  template <typename S, typename F = long long, typename = std::enable_if_t<std::is_signed_v<F>>>
  [[nodiscard]] Table<S, F> TraverseTree(const std::unique_ptr<Node_<F>> &node, const BinaryNumber &prefix)
  {
    using SymbolType = S;
    using FrequencyType = F;

    using InternalNodeType = InternalNode_<FrequencyType>;
    using LeafNodeType = LeafNode_<SymbolType, FrequencyType>;

    if (InternalNodeType *in = dynamic_cast<InternalNodeType *>(node.get()); in != nullptr)
    {
      Table<S, F> codes;
      BinaryNumber left_prefix = prefix;
      left_prefix.AppendBack(BinaryDigit::ZERO);
      codes.Append(TraverseTree<SymbolType>(in->left, left_prefix));

      BinaryNumber right_prefix = prefix;
      right_prefix.AppendBack(BinaryDigit::ONE);
      codes.Append(TraverseTree<SymbolType>(in->right, right_prefix));
      return codes;
    }
    else if (LeafNodeType *ln = dynamic_cast<LeafNodeType *>(node.get()); ln != nullptr)
    {
      BinaryNumber internal_prefix;
      if (prefix.empty())
        internal_prefix.AppendBack(BinaryDigit::ZERO);
      else
        internal_prefix = prefix;
      const Table<S, F> codes = {{ln->symbol, ln->frequency, internal_prefix}};
      return codes;
    }
    else
    {
      // Should never happen!
      throw std::runtime_error("ERROR: This should never happen, unknown Node_ Pointer detected. Aborting.");
    }
  }
#endif

  template<typename S>
  [[nodiscard]] constexpr std::size_t max_alphabet_size()
  {
    return (2 << sizeof(S) * 8);
  }

  template<typename S, typename F = long long>
  struct Entry
    {
      using SymbolType = S;
      using FrequencyType = F;
      explicit constexpr Entry(const SymbolType& s, const FrequencyType& f, const std::string& b) : 
        symbol(s), frequency(f), binary_code(b) {}
      SymbolType symbol;
      FrequencyType frequency;
      std::string binary_code;
    };
  /*!
   * \brief Encode This function creates Huffman codes for the passed symbols.

   * \param symbols The symbols to get the Huffman codes for

   * \return A table of codes for each individual symbol
   */
  template <typename S, std::size_t A, typename F = long long>
  [[nodiscard]] constexpr auto Encode(const std::vector<S> &payload)
  {
    using SymbolType = S;
    constexpr std::size_t AlphabetSize = A;
    using FrequencyType = F;

    std::size_t counter = 0;
    std::array<std::pair<SymbolType, FrequencyType>, AlphabetSize> frequencies;

    for (const SymbolType &symbol : payload)
    {
      if (auto t = std::find_if(frequencies.begin(), frequencies.end(), [&symbol](const auto &e)
                                { return e.first == symbol; });
          t != frequencies.end())
      {
        // element was not found, make sure to now add this to the array and increment the counter
        t->second += 1;
      }
      else
      {
        frequencies[counter] = std::make_pair(symbol, 1);
        ++counter;
      }
    }

    std::sort(frequencies.begin(), frequencies.end(), [](const auto &first, const auto &second)
              { return first.second > second.second; });

    
    std::array<Entry<S, F>, AlphabetSize> result;

    for (std::size_t i = 0; i != frequencies.size(); ++i)
    {
      result[i].symbol = frequencies[i].first;
      result[i].frequency = frequencies[i].second;
      result[i].binary_code = std::bitset<8>(i).to_string();
    }
    return result;
  }
}