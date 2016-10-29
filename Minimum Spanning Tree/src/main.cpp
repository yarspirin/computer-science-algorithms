#include <iostream>
#include <fstream>
#include <cassert>

#include "Graph.hpp"


// Execution
void run() {
  // std::ifstream in("kruskal.in");
  // std::ofstream out("kruskal.out");

  int num_vertices = 0, num_edges = 0;
  std::cin >> num_vertices >> num_edges;

  EdgeList<int> edge_list;
  for (int i = 0; i < num_edges; ++i) {
    int from = 0, to = 0, weight = 0;
    std::cin >> from >> to >> weight;

    from--, to--;

    edge_list.push_back(Edge<int>(from, to, weight));
    edge_list.push_back(Edge<int>(to, from, weight));
  }

  Graph<int> graph(num_vertices, num_edges, edge_list, new BoruvkaMSTFinder<int>());
  std::cout << "Boruvka algorithm have found MST with the total weight: " << graph.FindMinSpanningTree() << std::endl;

  graph.SetMSTFinder(new KruskalMSTFinder<int>());
  std::cout << "Kruskal algorithm have found MST with the total weight: " << graph.FindMinSpanningTree() << std::endl;

  graph.SetMSTFinder(new PrimMSTFinder<int>());
  std::cout << "Prim algorithm have found MST with the total weight: " << graph.FindMinSpanningTree() << std::endl;
}

int main() {
  run();
  return 0;
}