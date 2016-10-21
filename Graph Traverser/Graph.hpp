//
// Created by whoami on 04/03/16.
//

#ifndef GRAPH_TRAVERSER_GRAPH_HPP
#define GRAPH_TRAVERSER_GRAPH_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

// Forward declarations
template <typename VertexDataType, typename EdgeDataType>
class BFS;

template <typename VertexDataType, typename EdgeDataType>
class DFS;

// Class Graph implements graph based on adjacent lists
// Supports data storage in vertices and in edges

// But requires:- operator >>, operator << both for VertexDataType and EdgeDataType
//              - default constructors both for VertexDataType and EdgeDataType
template <typename VertexDataType, typename EdgeDataType>
class Graph {

  friend class BFS<VertexDataType, EdgeDataType>;
  friend class DFS<VertexDataType, EdgeDataType>;

 public:

  // Forward declarations
  struct Vertex {

    Vertex(int number_of_vertex = -1, VertexDataType vertex_data = VertexDataType())
        : number_of_vertex_(number_of_vertex),
          vertex_data_(vertex_data) {}

    int number_of_vertex_;
    VertexDataType vertex_data_;
  };
  struct Edge {

    Edge(int u = -1, int v = -1, EdgeDataType edge_data = EdgeDataType())
        : u_(u), v_(v), edge_data_(edge_data) {}

    int u_, v_;
    EdgeDataType edge_data_;
  };

  // Constructor
  Graph(size_t size, bool is_directed)
      : number_of_vertices_(size), is_directed_(is_directed),
        number_of_edges_(0) {

    adjacent_lists_.resize(number_of_vertices_);
    vertices_.resize(number_of_vertices_);

    for (int i = 0; i < number_of_vertices_; ++i) {
      vertices_[i].number_of_vertex_ = i;
    }

  }

  // Get number of vertices
  size_t vertices() const { return number_of_vertices_; }

  // Get number of edges
  size_t edges() const { return number_of_edges_; }

  // Check for directed graph
  bool is_directed() const { return is_directed_; }

  // Add vertex
  void add_vertex(VertexDataType vertex_data) {
    number_of_vertices_++;
    vertices_.push_back(Vertex((int)number_of_vertices_, vertex_data));
  }

  // Add edge
  void add_edge(int u, int v, EdgeDataType edge_data);

  // Check for availability of edge
  bool contains_edge(int u, int v) const;

  // Remove edge
  void remove_edge(int u, int v);

  // Get vector of vertices
  std::vector<typename Graph<VertexDataType, EdgeDataType>::Vertex> get_vertices() const;

  // Get vector of edges
  std::vector<typename Graph<VertexDataType, EdgeDataType>::Edge> get_edges() const;

  // Get vector of degrees
  std::vector<size_t> get_degrees() const;

  // Add edges from initializer_list
  void add_edges(std::initializer_list<Edge> &&list);

  // Read count vertices from stream is
  void read(int count = -1, std::istream &is = std::cin);

 private:

  // Find vertex v in adjacent list of u
  int search(int u, int v) const {

    for (int i = 0; i < adjacent_lists_[u].size(); ++i) {
      if (adjacent_lists_[u][i].v_ == v) {
        return i;
      }
    }

    return -1;
  }

  size_t number_of_vertices_;
  size_t number_of_edges_;
  bool is_directed_;

  // Vector of all vertices
  std::vector<Vertex> vertices_;

  // Vector of adjacent lists for each vertex
  std::vector<std::vector<Edge> > adjacent_lists_;
};

template <typename VertexDataType, typename EdgeDataType>
void Graph<VertexDataType, EdgeDataType>::add_edge(int u, int v, EdgeDataType edge_data) {

  assert(1 <= u && u <= vertices() && 1 <= v && v <= vertices());

  u--; v--;

  int pos = search(u, v);

  if (pos == -1) {
    number_of_edges_++;
    adjacent_lists_[u].push_back(Edge(u, v, edge_data));
  }

  if (!is_directed()) {
    pos = search(v, u);
    if (pos == -1) {
      number_of_edges_++;
      adjacent_lists_[v].push_back(Edge(v, u, edge_data));
    }
  }

}

template <typename VertexDataType, typename EdgeDataType>
bool Graph<VertexDataType, EdgeDataType>::contains_edge(int u, int v) const {

  assert(1 <= u && u <= vertices() && 1 <= v && v <= vertices());

  u--, v--;

  return search(u, v) != -1;
}

template <typename VertexDataType, typename EdgeDataType>
void Graph<VertexDataType, EdgeDataType>::remove_edge(int u, int v) {

  assert(1 <= u && u <= vertices() && 1 <= v && v <= vertices());

  u--; v--;

  if (contains_edge(u + 1, v + 1)) {
    number_of_edges_--;

    int pos = search(u, v);

    adjacent_lists_[u].erase(pos + adjacent_lists_[u].begin());

    if (!is_directed()) {
      pos = search(v, u);
      adjacent_lists_[v].erase(pos + adjacent_lists_[v].begin());
    }
  }

}

template <typename VertexDataType, typename EdgeDataType>
std::vector<typename Graph<VertexDataType, EdgeDataType>::Edge> Graph<VertexDataType, EdgeDataType>::get_edges() const {
  std::vector<Graph::Edge> result;

  for (size_t v = 0; v < adjacent_lists_.size(); ++v) {
    for (int i = 0; i < adjacent_lists_[v].size(); ++i) {
      result.push_back(adjacent_lists_[v][i]);
    }
  }

  return result;
}

template <typename VertexDataType, typename EdgeDataType>
std::vector<size_t> Graph<VertexDataType, EdgeDataType>::get_degrees() const {
  std::vector<size_t> result(vertices());

  for (size_t v = 0; v < adjacent_lists_.size(); ++v) {
    result[v] = adjacent_lists_[v].size();
  }

  return result;
}

template <typename VertexDataType, typename EdgeDataType>
void Graph<VertexDataType, EdgeDataType>::add_edges(std::initializer_list<Edge> &&edges) {
  for (auto&& edge : edges) {
    add_edge(edge.u_, edge.v_, edge.edge_data_);
  }
}

template <typename VertexDataType, typename EdgeDataType>
void Graph<VertexDataType, EdgeDataType>::read(int count, std::istream& is) {
  if (count < 0) {
    count = (int)number_of_vertices_;
  }

  VertexDataType vertex_data;

  for (int i = 0; i < count; ++i) {
    is >> vertex_data;
    add_vertex(vertex_data);
  }

}

template <typename VertexDataType, typename EdgeDataType>
std::vector<typename Graph<VertexDataType, EdgeDataType>::Vertex> Graph<VertexDataType, EdgeDataType>::get_vertices() const {
  return vertices_;
}

#endif //GRAPH_TRAVERSER_GRAPH_HPP

