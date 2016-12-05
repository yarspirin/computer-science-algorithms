//
// Created by whoami on 12/5/16.
//

#include <vector>

#include "../src/BinarySearchTree.h"
#include "../src/CartesianTree.h"

#include "gtest/gtest.h"

const std::vector<std::pair<int, int>> keys1 = {{5, 11},
                                               {18, 8},
                                               {25, 7},
                                               {50, 12},
                                               {30, 30},
                                               {15, 15},
                                               {20, 10},
                                               {22, 5},
                                               {40, 20},
                                               {45, 9}};

const std::vector<std::pair<int, int>> keys2 = {{38, 19},
                                                {37, 5},
                                                {47, 15},
                                                {35, 0},
                                                {12, 3},
                                                {0, 42},
                                                {31, 37},
                                                {21, 45},
                                                {30, 26},
                                                {41, 6}};

TEST(BasicTest, SampleTest1) {
  BinarySearchTree binary_search_tree;
  CartesianTree cartesian_tree;

  for (auto& key : keys1) {
    binary_search_tree.Put(key.first);
    cartesian_tree.Put(key.first, key.second);
  }

  ASSERT_EQ(binary_search_tree.GetHeight() - cartesian_tree.GetHeight(), 2);
  ASSERT_EQ(cartesian_tree.GetWidth() - binary_search_tree.GetWidth(), 1);
}

TEST(BasicTest, SampleTest2) {
  BinarySearchTree binary_search_tree;
  CartesianTree cartesian_tree;

  for (auto& key : keys2) {
    binary_search_tree.Put(key.first);
    cartesian_tree.Put(key.first, key.second);
  }

  ASSERT_EQ(binary_search_tree.GetHeight() - cartesian_tree.GetHeight(), 2);
  ASSERT_EQ(cartesian_tree.GetWidth() - binary_search_tree.GetWidth(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}