#include <iostream>
#include "Graph.h"

void run() {
  while (true) {

    int num_vertices = 0;
    std::cin >> num_vertices;

    if (num_vertices == 0) {
      break;
    }

    int source = 0, target = 0;
    std::cin >> source >> target;
    source -= 1;
    target -= 1;

    int num_edges = 0;
    std::cin >> num_edges;

    AdjacencyMatrix edge_capacities(static_cast<size_t>(num_vertices),
                                    std::vector<int>(static_cast<size_t>(num_vertices)));

    for (int i = 0; i < num_edges; ++i) {
      int from = 0, to = 0, capacity = 0;
      std::cin >> from >> to >> capacity;

      from -= 1;
      to -= 1;

      edge_capacities[from][to] += capacity;
      edge_capacities[to][from] += capacity;
    }

    Graph graph(edge_capacities);
    graph.SetSpecialVertices(source, target);
    std::cout << graph.FindMaxFlow() << std::endl;
  }
}

int main() {
  run();
  return 0;
}
