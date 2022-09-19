#include <iostream>

#include <gtest/gtest.h>

#include <lossless/entropy/huffman/huffman.h>

class HuffmanTest : public ::testing::Test
{
};

TEST_F(HuffmanTest, LeafNodeCorrectConstruction)
{
  huffman::LeafNode<char> node('d', 3);
  EXPECT_EQ(3, node.frequency);
  EXPECT_EQ('d', node.symbol);
}
TEST_F(HuffmanTest, LeafNodeFalseConstruction)
{
  EXPECT_ANY_THROW(huffman::LeafNode<char>('d', -3));
}
TEST_F(HuffmanTest, InternalNodeCorrectConstruction)
{
  std::unique_ptr<huffman::Node> left =
      std::make_unique<huffman::LeafNode<char>>('l', 2);
  auto const* const left_ptr = left.get();
  std::unique_ptr<huffman::Node> right =
      std::make_unique<huffman::LeafNode<char>>('r', 3);
  auto const* const right_ptr = right.get();
  huffman::InternalNode node(left, right);
  EXPECT_EQ(5, node.frequency);
  EXPECT_EQ(node.left.get(), left_ptr);
  EXPECT_EQ(node.right.get(), right_ptr);
}
TEST_F(HuffmanTest, InternalNodeFalseConstruction)
{
  std::unique_ptr<huffman::Node> left = nullptr;
  std::unique_ptr<huffman::Node> right = nullptr;
  EXPECT_DEATH(huffman::InternalNode node(left, right), "");
}
TEST_F(HuffmanTest, HuffmanCreateTable1)
{
  const std::vector<char> message = {'H', 'e', 'l', 'l', 'o'};
  huffman::Table<char> table = huffman::Encode(message);
  huffman::BinaryNumber l = {0};
  EXPECT_EQ(table['l'], l);
  huffman::BinaryNumber o = {1, 0};
  EXPECT_EQ(table['o'], o);
  huffman::BinaryNumber H = {1, 1, 0};
  EXPECT_EQ(table['H'], H);
  huffman::BinaryNumber e = {1, 1, 1};
  EXPECT_EQ(table['e'], e);
}
// int main(int argc, char** argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
