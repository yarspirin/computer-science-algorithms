//
// Created by whoami on 11/6/16.
//

#include <map>
#include <queue>

#include "Graph.h"

int Graph::FindMaxFlow() const {
  assert(IsValid());

  int flow_value = 0;

  AdjacencyMatrix residual_network = edge_capacities_;

  while (true) {
    EdgeList augmenting_path = GetShortestAugmentingPath(residual_network);

    if (augmenting_path.size() == 0) {
      break;
    }

    int min_capacity = std::numeric_limits<int>::max();
    for (auto& edge : augmenting_path) {
      min_capacity = std::min(min_capacity, edge.capacity);
    }

    for (auto& edge : augmenting_path) {
      if (residual_network[edge.from][edge.to] - min_capacity >= 0) {
        residual_network[edge.from][edge.to] -= min_capacity;
        residual_network[edge.to][edge.from] += min_capacity;
      }
    }

    flow_value += min_capacity;
  }

  return flow_value;
}

EdgeList Graph::GetShortestAugmentingPath(const AdjacencyMatrix &residual_network) const {
  EdgeList shortest_augmenting_path;

  std::vector<bool> used(static_cast<size_t>(num_vertices_), false);
  std::queue<int> vertices_queue;
  std::vector<int> moves_storage(static_cast<size_t>(num_vertices_));

  used[source_] = true;
  vertices_queue.push(source_);

  while (!vertices_queue.empty()) {
    int current_vertex = vertices_queue.front();
    vertices_queue.pop();

    if (current_vertex == target_) {
      shortest_augmenting_path = RecoverPath(residual_network, moves_storage);
      break;
    }

    for (int next_vertex = 0; next_vertex < num_vertices_; ++next_vertex) {
      if (residual_network[current_vertex][next_vertex] > 0 && !used[next_vertex]) {
        used[next_vertex] = true;
        vertices_queue.push(next_vertex);
        moves_storage[next_vertex] = current_vertex;
      }
    }
  }

  return shortest_augmenting_path;
}

EdgeList Graph::RecoverPath(const AdjacencyMatrix& residual_network, const std::vector<int>& moves_storage) const {
  EdgeList path;

  int current_vertex = target_;
  while (current_vertex != source_) {
    int previous_vertex = moves_storage[current_vertex];
    path.push_back(Edge(previous_vertex, current_vertex, residual_network[previous_vertex][current_vertex]));
    current_vertex = previous_vertex;
  }

  std::reverse(path.begin(), path.end());
  return path;
}