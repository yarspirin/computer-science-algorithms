//
// Created by whoami on 10/23/16.
//

#ifndef MST_GRAPH_HPP
#define MST_GRAPH_HPP

#include <memory>

#include "PrimMSTFinder.hpp"
#include "KruskalMSTFinder.hpp"
#include "BoruvkaMSTFinder.hpp"
#include "Edge.hpp"

// Main logic class
// Construct graph, manipulate it, run different MST algorithms
// Created in a way of Strategy Design Pattern
template <class WeightType>
class Graph {
 public:

  Graph() = delete;

  Graph(int num_vertices, int num_edges, const EdgeList<WeightType>& edge_list,
        MinSpanningTreeFinderInterface<WeightType>* mst_finder)

      : num_vertices_(num_vertices), num_edges_(num_edges), edge_list_(edge_list),
        mst_finder_(mst_finder) { }

  ~Graph() {
    if (mst_finder_) {
      delete mst_finder_;
    }
  }

  // Set or change the Minimum Spanning Tree algorithm
  void SetMSTFinder(MinSpanningTreeFinderInterface<WeightType>* mst_finder) {
    if (mst_finder_) {
      delete mst_finder_;
    }
    mst_finder_ = mst_finder;
  }

  // Build the Minimum Spanning Tree and return its total weight
  WeightType FindMinSpanningTree() {
    assert(mst_finder_);
    return mst_finder_->FindMinSpanningTree(num_vertices_, edge_list_);
  }

 private:

  int num_vertices_;
  int num_edges_;
  EdgeList<WeightType> edge_list_;
  MinSpanningTreeFinderInterface<WeightType>* mst_finder_;
};

#endif //MST_GRAPH_HPP
