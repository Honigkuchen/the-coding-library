#ifndef HUFFMAN_TYPES_H
#define HUFFMAN_TYPES_H

// STL includes
#include <vector>
#include <iostream>

namespace huffman
{
/*!
 * \brief The BinaryDigit enum TODO
 */
enum class BinaryDigit
{
    ZERO = 0,
    ONE = 1
};
/*!
 * TODO
 */
using BinaryNumber = std::vector<BinaryDigit>;
/*!
 * \brief operator << TODO
 * \param o
 * \param b
 * \return
 */
std::ostream& operator<<(std::ostream& o, const BinaryDigit& d)
{
    switch(d)
    {
    case BinaryDigit::ZERO:
        return o << "0";
    case BinaryDigit::ONE:
        return o << "1";
    }
}
std::ostream& operator<<(std::ostream& o, const BinaryNumber& n)
{
    for(const auto& digit : n)
        o << digit;
    return o;
}
}

#endif // HUFFMAN_TYPES_H
