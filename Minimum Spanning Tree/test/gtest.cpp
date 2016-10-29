//
// Created by whoami on 10/26/16.
//

#include "gtest/gtest.h"
#include "../src/Graph.hpp"
#include "samples.h"

TEST(BasicTest, Boruvka) {
  Graph<int> graph(4, 4, kSampleEdgeList, new BoruvkaMSTFinder<int>());
  EXPECT_EQ(7, graph.FindMinSpanningTree());
}

TEST(BasicTest, Kruskal) {
  Graph<int> graph(4, 4, kSampleEdgeList, new KruskalMSTFinder<int>());
  EXPECT_EQ(7, graph.FindMinSpanningTree());
}

TEST(BasicTest, Prim) {
  Graph<int> graph(4, 4, kSampleEdgeList, new PrimMSTFinder<int>());
  EXPECT_EQ(7, graph.FindMinSpanningTree());
}

TEST(TemplateTest, Integers) {
  Graph<int16_t> short_graph(4, 4, kShortEdgeList, new KruskalMSTFinder<int16_t>());
  EXPECT_EQ(7, short_graph.FindMinSpanningTree());

  Graph<int64_t> long_graph(4, 4, kLongEdgeList, new BoruvkaMSTFinder<int64_t>());
  EXPECT_EQ(7000000000, long_graph.FindMinSpanningTree());
}

TEST(TemplateTest, Reals) {
  Graph<float> float_graph(4, 4, kFloatEdgeList, new PrimMSTFinder<float>());
  EXPECT_EQ(7.0, float_graph.FindMinSpanningTree());

  Graph<double> double_graph(4, 4, kDoubleEdgeList, new BoruvkaMSTFinder<double>());
  EXPECT_EQ(700.0, double_graph.FindMinSpanningTree());
}

TEST(FatigueTest, HundredVertices) {
  int num_vertices = rand() % 99 + 1;

  EdgeList<int> edge_list;

  // Making graph connected
  for (int i = 0; i < num_vertices - 1; ++i) {
    int weight = rand() % 10000;
    edge_list.push_back(Edge<int>(i, i + 1, weight));
    edge_list.push_back(Edge<int>(i + 1, i, weight));
  }

  int num_edges = num_vertices - 1;

  int add_edges = (rand() % 5 + 1) * num_vertices;

  for (int i = 0; i < add_edges; ++i) {
    int from = rand() % num_vertices;
    int to = rand() % num_vertices;
    int weight = rand() % 10000;

    edge_list.push_back(Edge<int>(from, to, weight));
    edge_list.push_back(Edge<int>(to, from, weight));
    num_edges += 1;
  }

  Graph<int> graph(num_vertices, num_edges, edge_list, new BoruvkaMSTFinder<int>());
  int boruvka_result = graph.FindMinSpanningTree();

  graph.SetMSTFinder(new KruskalMSTFinder<int>());
  int kruskal_result = graph.FindMinSpanningTree();

  graph.SetMSTFinder(new PrimMSTFinder<int>());
  int prim_result = graph.FindMinSpanningTree();

  EXPECT_EQ(boruvka_result, kruskal_result);
  EXPECT_EQ(kruskal_result, prim_result);
  EXPECT_EQ(boruvka_result, prim_result);
}

TEST(FatigueTest, ThousandVertices) {
  int num_vertices = rand() % 999 + 1;

  EdgeList<int64_t> edge_list;

  // Making graph connected
  for (int i = 0; i < num_vertices - 1; ++i) {
    int64_t weight = rand() % 100000000;
    edge_list.push_back(Edge<int64_t>(i, i + 1, weight));
    edge_list.push_back(Edge<int64_t>(i + 1, i, weight));
  }

  int num_edges = num_vertices - 1;

  int add_edges = (rand() % 42 + 1) * num_vertices;

  for (int i = 0; i < add_edges; ++i) {
    int from = rand() % num_vertices;
    int to = rand() % num_vertices;
    int64_t weight = rand() % 100000000;

    edge_list.push_back(Edge<int64_t>(from, to, weight));
    edge_list.push_back(Edge<int64_t>(to, from, weight));
    num_edges += 1;
  }

  Graph<int64_t> graph(num_vertices, num_edges, edge_list, new BoruvkaMSTFinder<int64_t>());
  int64_t boruvka_result = graph.FindMinSpanningTree();

  graph.SetMSTFinder(new KruskalMSTFinder<int64_t>());
  int64_t kruskal_result = graph.FindMinSpanningTree();

  graph.SetMSTFinder(new PrimMSTFinder<int64_t>());
  int64_t prim_result = graph.FindMinSpanningTree();

  EXPECT_EQ(boruvka_result, kruskal_result);
  EXPECT_EQ(kruskal_result, prim_result);
  EXPECT_EQ(boruvka_result, prim_result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}