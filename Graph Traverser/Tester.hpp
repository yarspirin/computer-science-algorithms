//
// Created by whoami on 04/03/16.
//

#ifndef GRAPH_TRAVERSER_TESTER_HPP
#define GRAPH_TRAVERSER_TESTER_HPP

#include <cstdlib>

#include "Graph.hpp"
#include "Traversal.hpp"

struct VertexData {
  VertexData(int count = 0) : count_(count) {}

  int count_;

  friend std::istream& operator >> (std::istream& in, VertexData& vertexData) {
    in >> vertexData.count_;

    return in;
  }
  friend std::ostream& operator << (std::ostream& out, VertexData& vertexData) {
    out << vertexData.count_;

    return out;
  }
};

struct EdgeData {
  EdgeData(int w = 0) : w_(w) {}

  friend std::istream& operator >> (std::istream& in, EdgeData& edgeData) {
    in >> edgeData.w_;

    return in;
  }
  friend std::ostream& operator << (std::ostream& out, EdgeData& edgeData) {
    out << edgeData.w_;

    return out;
  }

  int w_;
};


template <typename VertexDataType, typename EdgeDataType>
class Tester {
 public:

  Tester(size_t number_of_vertices, size_t number_of_edges) {

    tests.resize(number_of_edges);

    for (size_t i = 0; i < number_of_edges; ++i) {
      tests[i] = typename Graph<VertexDataType, EdgeDataType>::Edge(rand() % number_of_vertices + 1, rand() % number_of_vertices + 1, i + 1);
    }
  }

  void test(Graph<VertexDataType, EdgeDataType>* graph) {
    for (size_t i = 0; i < tests.size(); ++i) {
      graph->add_edge(tests[i].u_, tests[i].v_, tests[i].edge_data_);
    }

    BFS<VertexData, EdgeData> bfs;
    DFS<VertexData, EdgeData> dfs;

    std::vector<int> colors1 = bfs(*graph);
    std::vector<int> colors2 = dfs(*graph);

    for (int i = 0; i < colors1.size(); ++i) {
      std::cout << colors1[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < colors2.size(); ++i) {
      std::cout << colors2[i] << " ";
    }
    std::cout << std::endl;
  }

 private:

  std::vector<typename Graph<VertexDataType, EdgeDataType>::Edge> tests;

  size_t number_of_vertices_;
  size_t number_of_edges;
};

#endif //GRAPH_TRAVERSER_TESTER_HPP
