#ifndef HUFFMAN_GRAPH_H
#define HUFFMAN_GRAPH_H

// STL includes
#include <memory>

namespace huffman
{
/*!
 * \brief The Node class TODO
 */
template<typename FrequencyType = long long, typename = std::enable_if_t<std::is_signed_v<FrequencyType>>>
class Node_
{
 public:
    /*!
     * \brief Node TODO
     * \param frequency
     */
    explicit Node_(const FrequencyType& frequency) :
		frequency(frequency)
	{
		if (frequency < 0)
			throw std::runtime_error("The frequency of a node must not be negative");
	}
    /*!
     * \brief ~Node TODO
     */
    virtual ~Node_() = default;
 public:
    const FrequencyType frequency; //! frequency TODO
};
using Node = Node_<>;
/*!
 * \brief The InternalNode class TODO
 */
template<typename FrequencyType = long long>
class InternalNode_ : public Node_<FrequencyType>
{
 public:
    /*!
     * \brief InternalNode TODO
     * \param n0
     * \param n1
     */
	 InternalNode_(std::unique_ptr<Node>& n0, std::unique_ptr<Node>& n1) :
        Node(n0->frequency + n1->frequency),
        left(std::move(n0)),
        right(std::move(n1)) {}
public:
    const std::unique_ptr<Node> left; //! left TODO
    const std::unique_ptr<Node> right; //! right TODO
};
using InternalNode = InternalNode_<>;
/*!
 * \brief The LeafNode class
 */
template<typename SymbolType, typename FrequencyType = long long>
class LeafNode_ : public Node_<FrequencyType>
{
 public:
    /*!
     * \brief LeafNode TODO
     * \param frequency
     * \param symbol
     */
	 LeafNode_(const FrequencyType& frequency, const SymbolType& symbol) :
        Node(frequency),
        symbol(symbol) {}
 public:
    const SymbolType symbol; //! symbol TODO
};
template<typename SymbolType>
using LeafNode = LeafNode_<SymbolType>;
}

#endif // HUFFMAN_GRAPH_H
