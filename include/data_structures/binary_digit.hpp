#pragma once
#ifndef CL_BINARY_DIGIT_HPP_
#define CL_BINARY_DIGIT_HPP_

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
} // namespace cl::data_structures

#endif