//
// Created by whoami on 10/24/16.
//

#ifndef MST_EDGE_HPP
#define MST_EDGE_HPP

#include <vector>
#include "MinSpanningTreeFinderInterface.hpp"

template <class WeightType>
const WeightType kInfinity = std::numeric_limits<WeightType>::max() / 2;

// Edge storage
template <class WeightType>
struct Edge {

  Edge() : from(-1), to(-1), weight(kInfinity<WeightType>) {}

  Edge(int _from, int _to, const WeightType& _weight)
      : from(_from), to(_to), weight(_weight) {}

  Edge GetReversedEdge() const {
    return Edge(to, from, weight);
  }

  bool operator < (const Edge& other) const {
    return weight < other.weight || (weight == other.weight &&
        (from < other.from || (from == other.from && to < other.to)));
  }

  int from, to;
  WeightType weight;
};

template <class WeightType>
using EdgeList = std::vector<Edge<WeightType>>;

#endif //MST_EDGE_HPP
