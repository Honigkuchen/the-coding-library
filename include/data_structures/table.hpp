#pragma once
#ifndef CL_TABLE_HPP_
#define CL_TABLE_HPP_

// STL includes
#include <algorithm>
#include <string>
#include <vector>

#ifdef CL_CPP20
#include <format>
#else
#include <sstream>
#endif

// Project includes
#include "../types.hpp"
#include "../utils/print.hpp"
#include "binary_number.hpp"

namespace cl::data_structures
{
/*!
 * \brief The Table class holds the Huffman codes for each individual symbol.
 *
 * The template parameter S is the symbol type and must be comparable to be inserted into a map.
 */
template <typename S>
class Table
{
public:
  using SymbolType = S;
  using FrequencyType = uint64_t;
  struct TableEntry
  {
    CL_CONSTEXPR CL_EXPLICIT TableEntry(const SymbolType& s, const FrequencyType& f, const BinaryNumber& n) : symbol(s),
                                                                                                              frequency(f),
                                                                                                              binary_number(n) {}
    SymbolType symbol;
    FrequencyType frequency;
    BinaryNumber binary_number;
  };
  using EntryType = TableEntry;

public:
  CL_CONSTEXPR Table() CL_NOEXCEPT = default;
  /*!
   *
   */
  CL_CONSTEXPR Table(EntryType&& e) CL_NOEXCEPT : symbols_{std::move(e)} {}
  /*!
   *
   */
  CL_CONSTEXPR Table(std::initializer_list<EntryType>&& v) CL_NOEXCEPT : symbols_(std::move(v)) {}
  /*!
   * \brief Table Creates a table with the passed data.
   * \param data The new data of the table
   */
  template <typename T>
  CL_EXPLICIT CL_CONSTEXPR Table(const T& data) : symbols_(data) {}
  /*!
   * \brief Table Creates a table with the passed data.
   *
   * The data is moved from the argument into the internal data structure thus being destroyed.
   *
   * \param data The new data of the table
   */
  template <typename T>
  CL_EXPLICIT CL_CONSTEXPR Table(T&& data) CL_NOEXCEPT : symbols_(std::move(data)) {}
  /*!
   * \brief operator [] Lookup operator for the table.
       *
   * \param symbol The symbol to get the Huffman code from

   * \return The Huffman binary number of the symbol
   */
  CL_NODISCARD CL_CONSTEXPR BinaryNumber operator[](const SymbolType& symbol) const
  {
    if (auto iter = std::find_if(symbols_.begin(), symbols_.end(), [&symbol](const EntryType& entry)
                                 {
                                   return entry.symbol == symbol;
                                 });
        iter != symbols_.end())
      return iter->binary_number;
    else
      return BinaryNumber();
  }
  template <typename T>
  friend std::string ToString(const Table<T>& table);
  /*!
   *
   */
  CL_CONSTEXPR void Append(const Table<S>& other)
  {
    symbols_.insert(symbols_.end(), other.symbols_.begin(), other.symbols_.end());
  }

  CL_NODISCARD auto begin() noexcept
  {
    return symbols_.begin();
  }
  CL_NODISCARD auto begin() const noexcept
  {
    return symbols_.begin();
  }
  CL_NODISCARD auto cbegin() const noexcept
  {
    return symbols_.begin();
  }
  CL_NODISCARD auto end() noexcept
  {
    return symbols_.end();
  }
  CL_NODISCARD auto end() const noexcept
  {
    return symbols_.end();
  }
  CL_NODISCARD auto cend() const noexcept
  {
    return symbols_.end();
  }

private:
  std::vector<EntryType> symbols_;
};
namespace details
{
template <class... Ts>
std::string ToString(const Ts&...) = delete;

template <typename T>
CL_NODISCARD std::string ToString(const Table<T>& table)
{
  std::stringstream ss;
  for (const typename Table<T>::EntryType& s : table.symbols_)
    ss << ToString(s);
  return ss.str();
}
template <typename S>
CL_NODISCARD std::string ToString(const typename Table<S>::EntryType& entry)
{
  std::stringstream ss;
  ss << "'" << entry.symbol << "': " << entry.frequency << " -> ";
  entry.binary_number.PrintOn(ss);
  return ss.str();
}
template <class T>
std::string ToString_impl(T const& t)
{
  return ToString(t);
}
} // namespace details

template <typename T>
CL_NODISCARD std::string ToString(const T& t)
{
  return details::ToString_impl(t);
}
} // namespace cl::data_structures

#endif