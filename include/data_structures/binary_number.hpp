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
#include "binary_digit.hpp"
namespace cl::data_structures
{
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
  void AppendBack(const BinaryDigit& d)
  {
    digits_.push_back(d);
  }
  void AppendBack(const unsigned short& d)
  {
    if (d == 0 || d == 1)
      digits_.push_back(BinaryDigit(d));
  }
  CL_CONSTEXPR void AppendBack(std::initializer_list<short unsigned int>&& new_digits)
  {
    for (const short unsigned int d : new_digits)
      AppendBack(d);
  }
  CL_NODISCARD auto begin() CL_NOEXCEPT
  {
    return digits_.begin();
  }
  CL_NODISCARD auto begin() const CL_NOEXCEPT
  {
    return digits_.begin();
  }
  CL_NODISCARD auto end() CL_NOEXCEPT
  {
    return digits_.end();
  }
  CL_NODISCARD auto end() const CL_NOEXCEPT
  {
    return digits_.end();
  }
  CL_NODISCARD bool empty() const CL_NOEXCEPT
  {
    return digits_.empty();
  }
  CL_NODISCARD std::size_t size() const CL_NOEXCEPT
  {
    return digits_.size();
  }
  CL_NODISCARD const BinaryDigit& operator[](const std::size_t& pos) const
  {
    return digits_[pos];
  }
  CL_NODISCARD const BinaryDigit& at(const std::size_t& pos) const
  {
    return digits_.at(pos);
  }
  CL_NODISCARD std::vector<cl::types::Byte> ToByteRepresentation() const CL_NOEXCEPT
  {
    CL_CONSTEXPR auto BitsPerByte = 8U;
    std::deque<BinaryDigit> local_copy = digits_;
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
      for (auto j = BitsPerByte - 1; j != 0; --j)
        if (expanded_binary_number[i + j] == BinaryDigit::ONE)
          b += static_cast<Byte>(std::pow(2, (BitsPerByte - 1 - j)));

      result.push_back(b);
    }
    return result;
  }
  bool operator==(const BinaryNumber& other) const CL_NOEXCEPT
  {
    if (digits_.size() != other.digits_.size())
      return false;
    for (auto this_iter = digits_.rbegin(), other_iter = other.digits_.rbegin();
         this_iter != digits_.rend() && other_iter != other.digits_.rend();
         ++this_iter, ++other_iter)
    {
      if (*this_iter != *other_iter)
        return false;
    }
    return true;
  }
  void swap(BinaryNumber& rhs) CL_NOEXCEPT
  {
    digits_.swap(rhs.digits_);
  }
  friend void swap(BinaryNumber& first, BinaryNumber& second) CL_NOEXCEPT;
  friend std::string ToString(const BinaryNumber& b);

private:
  std::deque<BinaryDigit> digits_;
};
void swap(BinaryNumber& first, BinaryNumber& second) CL_NOEXCEPT
{
  first.swap(second);
}
CL_NODISCARD std::string ToString(const BinaryNumber& b)
{
  std::stringstream ss;
  for (const BinaryDigit& digit : b.digits_)
    ss << ToString(digit);
  return ss.str();
}
} // namespace cl::data_structures

#endif // CL_BINARY_NUMBER_HPP_
