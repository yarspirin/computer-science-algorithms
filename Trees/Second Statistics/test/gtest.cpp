//
// Created by whoami on 12/12/16.
//

#include "../src/SegmentTree.h"
#include "gtest/gtest.h"

TEST(BasicTest, EasyTest) {
  std::vector<int> array = {2, 1, 5, 4, 3, 9, 10, 32};
  SegmentTree segment_tree;
  segment_tree.BuildTree(array);
  ASSERT_EQ(segment_tree.GetSecondStatistics(0, 7), 2);
  ASSERT_EQ(segment_tree.GetSecondStatistics(0, 3), 2);
  ASSERT_EQ(segment_tree.GetSecondStatistics(2, 5), 4);
}

TEST(BasicTest, WeirdTest) {
  std::vector<int> array = {3, 5, 1, 4};
  SegmentTree segment_tree;
  segment_tree.BuildTree(array);
  ASSERT_EQ(segment_tree.GetSecondStatistics(1, 2), 5);
  ASSERT_EQ(segment_tree.GetSecondStatistics(0, 1), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}