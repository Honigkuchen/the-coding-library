#pragma once

// STL includes
#include <string>
#include <vector>

// Project includes
#include "../../other/run_length_coding.h"
#include "huffman.h"
namespace cl::lossless::entropy::huffman
{
class ModifiedHuffmanCoding
{
public:
  [[nodiscard]] const auto encode(const std::vector<char>& symbols) const
  {
    cl::lossless::other::RunLengthCoding rlc;
    const std::vector<char> rlc_result = rlc.encode(symbols);
    for (const auto& c : rlc_result)
      std::cout << c;
    std::cout << std::endl;
    cl::lossless::entropy::huffman::HuffmanCoding hc;
    return hc.encode(rlc_result);
  }
};
} // namespace cl::lossless::entropy::huffman