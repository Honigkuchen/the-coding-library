#ifndef HUFFMAN_TYPES_H
#define HUFFMAN_TYPES_H

// STL includes
#include <vector>
#include <iostream>

namespace huffman
{
#if 0
	//using Byte = char;
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
	 * \brief TODO TODO
	 * \param o
	 * \param b
	 * \return
	 */
	void Print(const BinaryDigit& d, std::ostream& o = std::cout)
	{
		switch (d)
		{
		case BinaryDigit::ZERO:
			o << 0;
		case BinaryDigit::ONE:
			o << 1;
		}
	}
	/*!
	 * \brief Print TODO
	 */
	void Print(const BinaryNumber& n, std::ostream& o = std::cout)
	{
		for (const auto& b : n)
			Print(b, o);
	}
#endif
}

#endif // HUFFMAN_TYPES_H
