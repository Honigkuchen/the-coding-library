#include <iostream>

#include <gtest/gtest.h>

#include <data_structures/binary_number.h>
#include <lossless/entropy/huffman/huffman_modified.h>

class ModifiedHuffmanTest : public ::testing::Test
{
};

TEST_F(ModifiedHuffmanTest, LeafNodeCorrectConstruction)
{
  cl::data_structures::LeafNode<char> node('d', 3);
  EXPECT_EQ(3, node.frequency);
  EXPECT_EQ('d', node.symbol);
}
TEST_F(ModifiedHuffmanTest, LeafNodeFalseConstruction)
{
  EXPECT_ANY_THROW(cl::data_structures::LeafNode<char>('d', -3));
}
TEST_F(ModifiedHuffmanTest, InternalNodeCorrectConstruction)
{
  std::unique_ptr<cl::data_structures::Node> left =
      std::make_unique<cl::data_structures::LeafNode<char>>('l', 2);
  auto const* const left_ptr = left.get();
  std::unique_ptr<cl::data_structures::Node> right =
      std::make_unique<cl::data_structures::LeafNode<char>>('r', 3);
  auto const* const right_ptr = right.get();
  cl::data_structures::InternalNode node(left, right);
  EXPECT_EQ(5, node.frequency);
  EXPECT_EQ(node.left.get(), left_ptr);
  EXPECT_EQ(node.right.get(), right_ptr);
}
TEST_F(ModifiedHuffmanTest, InternalNodeFalseConstruction)
{
  std::unique_ptr<cl::data_structures::Node> left = nullptr;
  std::unique_ptr<cl::data_structures::Node> right = nullptr;
  EXPECT_DEATH(cl::data_structures::InternalNode node(left, right), "");
}
TEST_F(ModifiedHuffmanTest, HuffmanCreateTable1)
{
  constexpr auto create_test_char_vector = []()
  {
    const std::string test_string = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
    std::vector<char> result;
    for (const char& s : test_string)
      result.push_back(s);
    return result;
  };
  const std::vector<char> message = create_test_char_vector();
  cl::lossless::entropy::huffman::ModifiedHuffmanCoding mhc;
  cl::data_structures::Table<char>
      table = mhc.encode(message);
  cl::data_structures::BinaryNumber B = {0, 0};
  EXPECT_EQ(table['B'], B);
  cl::data_structures::BinaryNumber W = {0, 1};
  EXPECT_EQ(table['W'], W);
  cl::data_structures::BinaryNumber one = {1, 0};
  EXPECT_EQ(table['1'], one);
  cl::data_structures::BinaryNumber two = {1, 1, 1};
  EXPECT_EQ(table['2'], two);
  cl::data_structures::BinaryNumber three = {1, 1, 0, 0};
  EXPECT_EQ(table['3'], three);
  cl::data_structures::BinaryNumber four = {1, 1, 0, 1};
  EXPECT_EQ(table['4'], four);
}