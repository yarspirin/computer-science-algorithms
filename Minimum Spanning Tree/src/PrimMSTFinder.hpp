//
// Created by whoami on 10/23/16.
//

#ifndef MST_PRIMMSTFINDER_HPP
#define MST_PRIMMSTFINDER_HPP

#include <set>
#include <iostream>

#include "MinSpanningTreeFinderInterface.hpp"

template <class WeightType>
using AdjacentLists = std::vector<EdgeList<WeightType>>;

// Prim algorithm implementation
template <class WeightType>
class PrimMSTFinder : public MinSpanningTreeFinderInterface<WeightType> {
 public:
  // Build Minimum Spanning Tree and return its total weight
  WeightType FindMinSpanningTree(int num_vertices, const EdgeList<WeightType>& edge_list) const override;
 private:
  // Return graph presented as adjacent lists instead of edge list
  AdjacentLists<WeightType> ProduceAdjacentLists(int num_vertices, const EdgeList<WeightType>& edge_list) const;
};

template <class WeightType> AdjacentLists<WeightType> PrimMSTFinder<WeightType>::
ProduceAdjacentLists(int num_vertices, const EdgeList<WeightType> &edge_list) const {
  AdjacentLists<WeightType> result(static_cast<size_t>(num_vertices));

  for (auto& edge : edge_list) {
    result[edge.from].push_back(Edge<WeightType>(edge.from, edge.to, edge.weight));
  }

  return result;
}

// Present a pair (weight, index)
// Needed to speed up Prim algorithm
template <class WeightType>
struct WeightByIndex {

  WeightByIndex() {}

  WeightByIndex(WeightType _weight, int _index) : weight(_weight), index(_index) {}

  bool operator < (const WeightByIndex& other) const {
    return weight < other.weight || (weight == other.weight && index < other.index);
  }

  WeightType weight;
  int index;
};

template <class WeightType> WeightType PrimMSTFinder<WeightType>::
FindMinSpanningTree(int num_vertices, const EdgeList<WeightType>& edge_list) const {
  AdjacentLists<WeightType> adjacent_lists = ProduceAdjacentLists(num_vertices, edge_list);

  std::vector<WeightType> keys(static_cast<size_t>(num_vertices), kInfinity<WeightType>);
  keys[0] = 0;

  std::set<WeightByIndex<WeightType>> pending_vertices;
  pending_vertices.insert(WeightByIndex<WeightType>(0, 0));

  std::vector<bool> processed_vertices(static_cast<size_t>(num_vertices), false);

  while (!pending_vertices.empty()) {
    int min_key_vertex = pending_vertices.begin()->index;
    pending_vertices.erase(pending_vertices.begin());

    processed_vertices[min_key_vertex] = true;

    for (auto& edge : adjacent_lists[min_key_vertex]) {
      if (!processed_vertices[edge.to] && keys[edge.to] > edge.weight) {
        pending_vertices.erase(WeightByIndex<WeightType>(keys[edge.to], edge.to));
        keys[edge.to] = edge.weight;
        pending_vertices.insert(WeightByIndex<WeightType>(keys[edge.to], edge.to));
      }
    }

  }

  WeightType total_weight = 0;
  for (int i = 0; i < keys.size(); ++i) {
    total_weight += keys[i];
  }

  return total_weight;
}

#endif //MST_PRIMMSTFINDER_HPP
