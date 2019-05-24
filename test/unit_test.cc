#include <iostream>

#include <gtest/gtest.h>

#include <huffman.h>

class HuffmanTest : public ::testing::Test {};

TEST_F(HuffmanTest, LeafNodeConstruction)
{
    huffman::LeafNode node(3, 'd');
    EXPECT_EQ(3, node.frequency);
    EXPECT_EQ('d', node.symbol);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
