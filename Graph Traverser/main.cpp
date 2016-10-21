#include <iostream>

#include "Graph.hpp"
#include "Traversal.hpp"
#include "Tester.hpp"

int main() {

  size_t n = 0, m = 0;
  std::cin >> n >> m;

  Graph<VertexData, EdgeData> graph(n, true);

  Tester<VertexData, EdgeData> tester(n, m);

  std::vector<Graph<VertexData, EdgeData>::Vertex> vertices = graph.get_vertices();

  tester.test(&graph);

  std::cout << "Vertices are :" << std::endl << std::endl;

  for (int i = 0; i < vertices.size(); ++i) {
    std::cout << vertices[i].number_of_vertex_ << " " << vertices[i].vertex_data_ << std::endl;
  }

  std::cout << "Edges are :" << std::endl << std::endl;

  std::vector<Graph<VertexData, EdgeData>::Edge> edges = graph.get_edges();

  for (int i = 0; i < edges.size(); ++i) {
    std::cout << edges[i].u_ << " " << edges[i].v_ << " " << edges[i].edge_data_ << std::endl;
  }

  return 0;
}