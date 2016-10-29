//
// Created by whoami on 10/23/16.
//

#ifndef MST_KRUSKALMSTFINDER_HPP
#define MST_KRUSKALMSTFINDER_HPP

#include "MinSpanningTreeFinderInterface.hpp"
#include "DisjointSetUnion.h"

// Kruskal algorithm implementation
// Based on disjoint-set union data structure to speed up
template <class WeightType>
class KruskalMSTFinder : public MinSpanningTreeFinderInterface<WeightType> {
 public:
  // Build Minimum Spanning Tree and return its total weight
  WeightType FindMinSpanningTree(int num_vertices_, const EdgeList<WeightType>& edge_list_) const override;
};

template <class WeightType> WeightType KruskalMSTFinder<WeightType>::
FindMinSpanningTree(int num_vertices_, const EdgeList<WeightType>& edge_list_) const {
  DisjointSetUnion disjoint_set_union;
  disjoint_set_union.InitDSU(num_vertices_);

  for (int i = 0; i < num_vertices_; ++i) {
    disjoint_set_union.CreateElementarySet(i);
  }

  // Avoiding corrupting data
  EdgeList<WeightType> copy_edge_list = edge_list_;

  std::sort(copy_edge_list.begin(), copy_edge_list.end());

  WeightType total_weight = 0;

  for (auto& edge : copy_edge_list) {
    if (disjoint_set_union.GetRepresentativeOfSet(edge.from) != disjoint_set_union.GetRepresentativeOfSet(edge.to)) {
      disjoint_set_union.UniteSets(edge.from, edge.to);
      total_weight += edge.weight;
    }
  }

  return total_weight;
}

#endif //MST_KRUSKALMSTFINDER_HPP
