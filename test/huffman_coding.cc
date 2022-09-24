#include <iostream>

#include <gtest/gtest.h>

#include <lossless/entropy/huffman/huffman.h>

class HuffmanTest : public ::testing::Test
{
};

TEST_F(HuffmanTest, LeafNodeCorrectConstruction)
{
  cl::data_structures::LeafNode<char> node('d', 3);
  EXPECT_EQ(3, node.frequency);
  EXPECT_EQ('d', node.symbol);
}
TEST_F(HuffmanTest, LeafNodeFalseConstruction)
{
  EXPECT_ANY_THROW(cl::data_structures::LeafNode<char>('d', -3));
}
TEST_F(HuffmanTest, InternalNodeCorrectConstruction)
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
TEST_F(HuffmanTest, InternalNodeFalseConstruction)
{
  std::unique_ptr<cl::data_structures::Node> left = nullptr;
  std::unique_ptr<cl::data_structures::Node> right = nullptr;
  EXPECT_DEATH(cl::data_structures::InternalNode node(left, right), "");
}
TEST_F(HuffmanTest, HuffmanCreateTable1)
{
  const std::vector<char> message = {'H', 'e', 'l', 'l', 'o'};
  cl::lossless::entropy::huffman::HuffmanCoding hc;
  cl::data_structures::Table<char>
      table = hc.encode(message);
  cl::data_structures::BinaryNumber l = {0};
  EXPECT_EQ(table['l'], l);
  cl::data_structures::BinaryNumber o = {1, 0};
  EXPECT_EQ(table['o'], o);
  cl::data_structures::BinaryNumber H = {1, 1, 0};
  EXPECT_EQ(table['H'], H);
  cl::data_structures::BinaryNumber e = {1, 1, 1};
  EXPECT_EQ(table['e'], e);
}