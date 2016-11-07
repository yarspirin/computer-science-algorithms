//
// Created by whoami on 11/7/16.
//

#include "gtest/gtest.h"
#include "../src/Graph.h"
#include "samples.h"

TEST(BasicTest, SampleTest) {
  Graph graph(kSampleMatrix);
  graph.SetSpecialVertices(0, 3);
  EXPECT_EQ(graph.FindMaxFlow(), 25);
}

TEST(BasicTest, Invalidity) {
  Graph graph(kSampleMatrix);
  EXPECT_EQ(graph.IsValid(), false);
}

TEST(BasicTest, Validity) {
  Graph graph(kSampleMatrix);
  graph.SetSpecialVertices(0, 3);
  EXPECT_EQ(graph.IsValid(), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}