#ifndef CL_BINARY_NUMBER_HPP_
#define CL_BINARY_NUMBER_HPP_

// C includes
#include <math.h>

// C++ includes
#include <queue>
#include <sstream>
#include <string_view>

// Project includes
#include "../defines.hpp"
#include "../types.hpp"

namespace cl::data_structures
{
/*!
 * \brief enum class BinaryDigit This enum represents the two binary digits zero and one.
 */
enum class BinaryDigit
{
  ZERO = 0,
  ONE = 1
};
/*!
 * \brief ToString This function converts a binary digit to it's specific std::string_view representation.
 *
 * \param d The digit to print
 */
CL_NODISCARD std::string_view ToString(const BinaryDigit& d)
{
  switch (d)
  {
  case BinaryDigit::ZERO:
    return "0";
  case BinaryDigit::ONE:
    return "1";
  }
  return "";
}
/*!
 * \brief ToString This function converts a byte in binary representation to it's specific std::string representation.
 *
 * \param b The byte to print
 */
CL_NODISCARD std::string ToString(const cl::types::Byte& b)
{
  std::stringstream ss;
  for (uint8_t i = 7; i != 0; --i)
  {
    const uint8_t mask = 1 << i;
    if ((b & mask) != 0)
      ss << ToString(BinaryDigit::ONE);
    else
      ss << ToString(BinaryDigit::ZERO);
  }
  return ss.str();
}
/*!
 * \brief class BinaryNumber
 */
class BinaryNumber
{
public:
  BinaryNumber() = default;
  BinaryNumber(const BinaryNumber& other) = default;
  BinaryNumber& operator=(const BinaryNumber& other) = default;
  BinaryNumber(BinaryNumber&& other) CL_NOEXCEPT = default;
  BinaryNumber& operator=(BinaryNumber&& other) CL_NOEXCEPT = default;

  BinaryNumber(std::initializer_list<short unsigned int>&& new_digits) CL_NOEXCEPT
  {
    AppendBack(std::move(new_digits));
  }
  void PrintOn(std::ostream& o) const
  {
    for (const BinaryDigit& digit : digits)
      o << ToString(digit);
  }
  void AppendBack(const BinaryDigit& d)
  {
    digits.push_back(d);
  }
  void AppendBack(const unsigned short& d)
  {
    if (d == 0 || d == 1)
      digits.push_back(BinaryDigit(d));
  }
  CL_CONSTEXPR void AppendBack(std::initializer_list<short unsigned int>&& new_digits)
  {
    for (const short unsigned int d : new_digits)
      AppendBack(d);
  }
  [[nodiscard]] auto begin() CL_NOEXCEPT
  {
    return digits.begin();
  }
  [[nodiscard]] auto begin() const CL_NOEXCEPT
  {
    return digits.begin();
  }
  [[nodiscard]] auto end() CL_NOEXCEPT
  {
    return digits.end();
  }
  [[nodiscard]] auto end() const CL_NOEXCEPT
  {
    return digits.end();
  }
  [[nodiscard]] bool empty() const CL_NOEXCEPT
  {
    return digits.empty();
  }
  [[nodiscard]] std::size_t size() const CL_NOEXCEPT
  {
    return digits.size();
  }
  [[nodiscard]] const BinaryDigit& operator[](const std::size_t& pos) const
  {
    return digits[pos];
  }
  [[nodiscard]] const BinaryDigit& at(const std::size_t& pos) const
  {
    return digits.at(pos);
  }
  CL_NODISCARD std::vector<cl::types::Byte> ToByteRepresentation() const CL_NOEXCEPT
  {
    CL_CONSTEXPR auto BitsPerByte = 8;
    std::deque<BinaryDigit> local_copy = digits;
    using cl::types::Byte;
    auto remainder = BitsPerByte - (local_copy.size() % BitsPerByte);
    std::deque<BinaryDigit> expanded_binary_number(remainder);
    for (std::size_t i = 0; i < remainder; ++i)
      expanded_binary_number[i] = BinaryDigit::ZERO;

    const auto iterator = expanded_binary_number.begin() + remainder;

    expanded_binary_number.insert(iterator, local_copy.begin(), local_copy.end());

    std::vector<Byte> result;
    result.reserve(static_cast<std::size_t>(std::ceil(expanded_binary_number.size() / BitsPerByte)));

    for (std::size_t i = 0; i < expanded_binary_number.size(); i += BitsPerByte)
    {
      Byte b = 0b00000000;
      for (auto j = BitsPerByte - 1; j >= 0; --j)
        if (expanded_binary_number[i + j] == BinaryDigit::ONE)
          b += static_cast<Byte>(std::pow(2, (BitsPerByte - 1 - j)));

      result.push_back(b);
    }
    return result;
  }
  bool operator==(const BinaryNumber& other) const CL_NOEXCEPT
  {
    if (digits.size() != other.digits.size())
      return false;
    for (auto this_iter = digits.rbegin(), other_iter = other.digits.rbegin();
         this_iter != digits.rend() && other_iter != other.digits.rend();
         ++this_iter, ++other_iter)
    {
      if (*this_iter != *other_iter)
        return false;
    }
    return true;
  }
  void swap(BinaryNumber& rhs) CL_NOEXCEPT
  {
    digits.swap(rhs.digits);
  }
  friend void swap(BinaryNumber& first, BinaryNumber& second) CL_NOEXCEPT
  {
    first.swap(second);
  }

private:
  std::deque<BinaryDigit> digits;
};
} // namespace cl::data_structures

#endif // CL_BINARY_NUMBER_HPP_
