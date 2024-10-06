#include <iostream>

#include <gtest/gtest.h>

#include <lossless/entropy/huffman/huffman.hpp>

TEST(HuffmanTest, LeafNodeCorrectConstruction)
{
  cl::data_structures::LeafNode<char> node('d', 3);
  EXPECT_EQ(3, node.frequency);
  EXPECT_EQ('d', node.symbol);
}
TEST(HuffmanTest, InternalNodeCorrectConstruction)
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
TEST(HuffmanTest, HuffmanCreateTable1)
{
  const std::vector<char> message = {'H', 'e', 'l', 'l', 'o'};
  cl::lossless::entropy::huffman::HuffmanCoding hc;
  cl::data_structures::Table<char>
      table = hc.encode(message);
  cl::data_structures::BinaryNumber l = {0U};
  EXPECT_EQ(table['l'], l);
  cl::data_structures::BinaryNumber o = {1U, 0U};
  EXPECT_EQ(table['o'], o);
  cl::data_structures::BinaryNumber H = {1U, 1U, 0U};
  EXPECT_EQ(table['H'], H);
  cl::data_structures::BinaryNumber e = {1U, 1U, 1U};
  EXPECT_EQ(table['e'], e);
}