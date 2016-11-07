//
// Created by whoami on 11/6/16.
//

#ifndef MAX_FLOW_PROBLEM_GRAPH_H
#define MAX_FLOW_PROBLEM_GRAPH_H

#include <vector>
#include <iostream>
#include <map>
#include <cassert>

struct Edge {

  Edge(int _from = 0, int _to = 0, int _capacity = 0)
      : from(_from), to(_to), capacity(_capacity) { }

  int from, to;
  int capacity;
};

using EdgeList = std::vector<Edge>;
using AdjacencyMatrix = std::vector<std::vector<int>>;

class Graph {
 public:
  Graph() = delete;

  Graph(const AdjacencyMatrix& edge_capacities)
      : num_vertices_(static_cast<int>(edge_capacities.size())),
        edge_capacities_(edge_capacities),
        is_valid_(false) { }

  // Change source and target vertices
  void SetSpecialVertices(int source, int target) {
    assert(source < num_vertices_ && target < num_vertices_);
    source_ = source;
    target_ = target;
    is_valid_ = true;
  }

  // Check if work state prepared for finding max flow
  bool IsValid() const {
    return is_valid_;
  }

  // Find the maximum flow in the flow network (based on Edmonds-Karp algorithm)
  int FindMaxFlow() const;

 private:
  // Return the shortest augmenting path in residual network (based on BFS algorithm)
  EdgeList GetShortestAugmentingPath(const AdjacencyMatrix& residual_network) const;

  // Help to find the shortest augmenting path
  EdgeList RecoverPath(const AdjacencyMatrix& residual_network, const std::vector<int>& moves_storage) const;

  bool is_valid_;
  int source_, target_;
  int num_vertices_;
  AdjacencyMatrix edge_capacities_;
};


#endif //MAX_FLOW_PROBLEM_GRAPH_H
