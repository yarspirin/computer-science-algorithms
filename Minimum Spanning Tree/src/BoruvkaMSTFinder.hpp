//
// Created by whoami on 10/23/16.
//

#ifndef MST_BORUVKAMSTFINDER_HPP
#define MST_BORUVKAMSTFINDER_HPP

#include <unordered_map>

#include "MinSpanningTreeFinderInterface.hpp"
#include "DisjointSetUnion.h"

// Boruvka algorithm implementation
template <class WeightType>
class BoruvkaMSTFinder : public MinSpanningTreeFinderInterface<WeightType> {
 public:
  // Build Minimum Spanning Tree and return its total weight
  WeightType FindMinSpanningTree(int num_vertices_, const EdgeList<WeightType>& edge_list_) const override;
};

template <class WeightType> WeightType BoruvkaMSTFinder<WeightType>::
FindMinSpanningTree(int num_vertices_, const EdgeList<WeightType>& edge_list_) const {
  DisjointSetUnion disjoint_set_union;
  disjoint_set_union.InitDSU(num_vertices_);

  for (int i = 0; i < num_vertices_; ++i) {
    disjoint_set_union.CreateElementarySet(i);
  }

  WeightType total_weight = 0;

  // For every vertex matches the most relevant edge to add
  std::vector<Edge<WeightType>> mapped_edge;

  // Edges to be added during iteration
  std::set<Edge<WeightType>> mst_edges;

  // While there are more than one component
  while (disjoint_set_union.GetLeaderSubsetSize(0) != num_vertices_) {
    mst_edges.clear();
    mapped_edge.assign(static_cast<size_t>(num_vertices_), Edge<WeightType>());

    for (auto& edge : edge_list_) {
      int from_representative = disjoint_set_union.GetRepresentativeOfSet(edge.from);
      int to_representative = disjoint_set_union.GetRepresentativeOfSet(edge.to);

      if (from_representative == to_representative) {
        continue;
      }

      mapped_edge[from_representative] = std::min(mapped_edge[from_representative], edge);
      mapped_edge[from_representative] = std::min(mapped_edge[from_representative], edge.GetReversedEdge());
    }

    for (auto& mapped_value : mapped_edge) {
      if (mapped_value.from == -1 && mapped_value.to == -1) {
        continue;
      }

      mst_edges.insert(mapped_value);
      disjoint_set_union.UniteSets(mapped_value.from, mapped_value.to);
    }

    for (auto& edge : mst_edges) {
      total_weight += edge.weight;
    }
  }

  return total_weight;
}

#endif //MST_BORUVKAMSTFINDER_HPP
