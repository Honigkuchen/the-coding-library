#ifndef HUFFMAN_TABLE_H
#define HUFFMAN_TABLE_H

// STL includes
#include <map>

// Project includes
#include "types.h"

namespace huffman
{
/*!
 * \brief The Table class TODO
 */
template<typename SymbolType>
class Table
{
public:
    /*!
     * \brief Table TODO
     */
    explicit Table() {}
    /*!
     * \brief Table TODO
     * \param data
     */
    template<typename T>
    explicit Table(const T& data) :
        symbols_(data) {}
    /*!
     * \brief Table TODO
     * \param data
     */
    template<typename T>
    explicit Table(T&& data) :
        symbols_(std::move(data)) {}
    /*!
     * \brief operator [] TODO
     * \param symbol
     * \return
     */
    BinaryNumber operator[](const SymbolType& symbol) const
    {
        if(auto iter = symbols_.find(symbol); iter != symbols_.end())
            return iter->second;
        else return BinaryNumber();
    }
	void PrintOn(std::ostream& o) const
	{
		for (const auto& [k, v] : symbols_)
		{
			o << k << " -> ";
			v.PrintOn(o);
			o << std::endl;
		}
	}
private:
    std::map<SymbolType, BinaryNumber> symbols_;
};
}

#endif // HUFFMAN_TABLE_H
