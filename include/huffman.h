#ifndef HUFFMAN_H
#define HUFFMAN_H

#ifndef __cplusplus
#error This library can only be used in C++.
#else
#if !(__cplusplus >= 201703L || _MSVC_LANG >= 201703L)
#error C++17 is needed for this library.
#endif
#endif

// STL includes
#include <vector>
#include <deque>
#include <memory>
#include <algorithm>

// Project includes
#include "binary_number.h"
#include "table.h"
#include "graph.h"

namespace huffman
{
/*!
 * \brief TraverseTree TODO
 * \param node
 * \param prefix
 * \return
 */
template<typename SymbolType>
std::map<SymbolType, BinaryNumber> TraverseTree(const std::unique_ptr<Node>& node, const BinaryNumber& prefix)
{
    std::map<SymbolType, BinaryNumber> result;

    if(LeafNode<SymbolType>* ln = dynamic_cast<LeafNode<SymbolType>*>(node.get()); ln != nullptr)
    {
        BinaryNumber internal_prefix;
        if(prefix.empty()) internal_prefix.AppendBack(BinaryDigit::ZERO);
        else internal_prefix = prefix;
        std::map<SymbolType, BinaryNumber> codes;
        codes[ln->symbol] = internal_prefix;
        return codes;
    }
    else if(InternalNode* in = dynamic_cast<InternalNode*>(node.get()); in != nullptr)
    {
        std::map<SymbolType, BinaryNumber> codes, left_codes, right_codes;
        BinaryNumber left_prefix = prefix;
        left_prefix.AppendBack(BinaryDigit::ZERO);
        left_codes = TraverseTree<SymbolType>(in->left, left_prefix);
        codes.insert(left_codes.begin(), left_codes.end());
        BinaryNumber right_prefix = prefix;
        right_prefix.AppendBack(BinaryDigit::ONE);
        right_codes = TraverseTree<SymbolType>(in->right, right_prefix);
        codes.insert(right_codes.begin(), right_codes.end());
        return codes;
    }
    else
    {
        // Should never happen!
        throw std::runtime_error("ERROR: This should never happen, unknown Node Pointer detected. Aborting.");
    }
}

/*!
 * \brief Encode TODO
 * \param symbols
 * \return
 */
template<typename SymbolType>
Table<SymbolType> Encode(const std::vector<SymbolType>& symbols)
{
    std::map<SymbolType, std::size_t> frequencies;

    for(const SymbolType& symbol : symbols)
    {
        if(auto iter = frequencies.find(symbol); iter != frequencies.end())
            ++iter->second;
        else
            frequencies.insert(std::make_pair(symbol, 1));
    }

    std::deque<std::unique_ptr<Node>> nodes;

    for(const auto& [symbol, frequency] : frequencies)
        nodes.push_back(std::make_unique<LeafNode<SymbolType>>(frequency, symbol));

    constexpr auto NodeComparator = [](const std::unique_ptr<Node>& lhs, const std::unique_ptr<Node>& rhs)
    {
        return lhs->frequency < rhs->frequency;
    };

    std::sort(nodes.begin(), nodes.end(), NodeComparator);

    while(nodes.size() > 1)
    {
        std::unique_ptr<Node> right_child = std::move(nodes.front());
        nodes.pop_front();
        std::unique_ptr<Node> left_child = std::move(nodes.front());
        nodes.pop_front();
        nodes.push_front(std::make_unique<InternalNode>(right_child, left_child));
        std::sort(nodes.begin(), nodes.end(), NodeComparator);
    }

    std::unique_ptr<Node> root = std::move(nodes.front());

    return Table<SymbolType>(TraverseTree<SymbolType>(root, {}));
}

}

#endif // HUFFMAN_H
