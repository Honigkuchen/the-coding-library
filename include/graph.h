#ifndef HUFFMAN_GRAPH_H
#define HUFFMAN_GRAPH_H

// STL includes
#include <memory>

namespace huffman
{
/*!
 * \brief The Node class TODO
 */
class Node
{
 public:
    /*!
     * \brief Node TODO
     * \param frequency
     */
    explicit Node(const std::size_t& frequency) :
        frequency(frequency) {}
    /*!
     * \brief ~Node TODO
     */
    virtual ~Node() = default;
 public:
    const std::size_t frequency; //! frequency TODO
};
/*!
 * \brief The InternalNode class TODO
 */
class InternalNode : public Node
{
 public:
    /*!
     * \brief InternalNode TODO
     * \param n0
     * \param n1
     */
    InternalNode(std::unique_ptr<Node>& n0, std::unique_ptr<Node>& n1) :
        Node(n0->frequency + n1->frequency),
        left(std::move(n0)),
        right(std::move(n1)) {}
public:
    const std::unique_ptr<Node> left; //! left TODO
    const std::unique_ptr<Node> right; //! right TODO
};
/*!
 * \brief The LeafNode class
 */
template<typename SymbolType>
class LeafNode : public Node
{
 public:
    /*!
     * \brief LeafNode TODO
     * \param frequency
     * \param symbol
     */
    LeafNode(const std::size_t& frequency, const SymbolType& symbol) :
        Node(frequency),
        symbol(symbol) {}
 public:
    const SymbolType symbol; //! symbol TODO
};
}

#endif // HUFFMAN_GRAPH_H
