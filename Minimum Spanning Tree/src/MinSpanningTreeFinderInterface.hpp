//
// Created by whoami on 10/23/16.
//

#ifndef MST_MINSPANNINGTREEFINDERINTERFACE_HPP
#define MST_MINSPANNINGTREEFINDERINTERFACE_HPP

#include <limits>

#include "Graph.hpp"
#include "Edge.hpp"

// Interface for MST-family algorithms
template <class WeightType>
class MinSpanningTreeFinderInterface {
 public:
  // Build Minimum Spanning Tree and return its total weight
  virtual WeightType FindMinSpanningTree(int num_vertices, const EdgeList<WeightType>& edge_list) const = 0;

  virtual ~MinSpanningTreeFinderInterface() { }
};

#endif //MST_MINSPANNINGTREEFINDERINTERFACE_HPP
