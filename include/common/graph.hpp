#ifndef CL_GRAPH_HPP_
#define CL_GRAPH_HPP_

// STL includes
#include <memory>
#include <type_traits>

// Project defines
#include "../defines.hpp"

namespace cl::data_structures
{
/*!
 * \brief The Node_ class represents a node in the Huffman graph.
 *
 * Each node has a frequency for the represented symbol or for the intermediate
 * node. The frequency is represented by the template parameter T. The type must
 * meet the std::is_signed requirement.
 *
 * @see LeafNode_
 * @see InternalNode_
 */
class Node_
{
public:
  /*! \brief The type of the frequency. */
  using FrequencyType = uint64_t;
  /*!
   * \brief Node_ Creates a Node_ object with a specified frequency for the
   * represented symbol.
   *
   * If the symbol is lower than zero a runtime error is thrown.
   *
   * \param frequency The frequency of the symbol
   */
  CL_EXPLICIT CL_CONSTEXPR Node_(const FrequencyType& frequency) : frequency(frequency) {}
  // Prevent slicing
  Node_(const Node_&) = delete;
  Node_& operator=(const Node_&) = delete;
  /*!
   * \brief ~Node_ Default Node_ destructor.
   */
  virtual ~Node_() = default;
  const FrequencyType frequency; //! frequency This is the frequency of the symbol or of the
                                 //! intermediate node in thje graph.
};
/*!
 * \brief Default node type, default frequency type is 'long long'.
 */
using Node = Node_;
/*!
 * \brief The InternalNode_ class represents an internal node in the Huffman
 * graph.
 *
 * An InternalNode_ does not represent a single symbol. The assigned frequency
 * is the sum of the child nodes. The template parameter FrequencyType is 'long
 * long' by default and must meet the std::is_signed requirement.
 *
 * @see Node_
 * @see LeafNode_
 */
class InternalNode_ : public Node_
{
public:
  /*!
   * \brief InternalNode_ Creates an internal node in the Huffman graph by
   * setting the child nodes. \param left The left child node \param right The
   * right child node
   */
  InternalNode_(std::unique_ptr<Node_>& left,
                std::unique_ptr<Node_>& right)
      : Node(left->frequency + right->frequency), left(std::move(left)),
        right(std::move(right))
  {
  }
  const std::unique_ptr<Node> left;  //! left The left child node
  const std::unique_ptr<Node> right; //! right The right child node
};
/*!
 * \brief Default internal node type, default frequency type is 'long long'.
 */
using InternalNode = InternalNode_;
/*!
 * \brief The LeafNode_ class represents the leafes of the Huffman graph.
 *
 * Each leaf node represents a single symbol. Each symbol occurs with a spcified
 * frequency. The frequency type must meet the std::is_signed requirement.
 *
 * @see Node_
 * @see InternalNode_
 */
template <typename S>
class LeafNode_ : public Node_
{
public:
  /*! \brief The type of the symbol. */
  using SymbolType = S;
  /*! \brief The type of the frequency. */
  using FrequencyType = Node_::FrequencyType;
  /*!
   * \brief LeafNode_ Creates a leaf node for a given symbol and frequency.
   * \param symbol The symbol represented by this node
   * \param frequency The frequency of the symbol
   */
  CL_EXPLICIT CL_CONSTEXPR LeafNode_(const SymbolType& symbol, const FrequencyType& frequency) CL_NOEXCEPT : Node_(frequency), symbol(symbol) {}
  const SymbolType symbol; //! symbol The symbol represented by this node
};
template <typename SymbolType>
using LeafNode = LeafNode_<SymbolType>;
} // namespace cl::data_structures

#endif // CL_GRAPH_HPP_