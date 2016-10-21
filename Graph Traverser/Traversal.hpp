//
// Created by whoami on 04/03/16.
//

#ifndef GRAPH_TRAVERSER_TRAVERSAL_HPP
#define GRAPH_TRAVERSER_TRAVERSAL_HPP

#include <iostream>
#include <queue>

#include "Graph.hpp"

// Colors of vertices
enum Colors {
  WHITE,
  GRAY,
  BLACK
};

template <typename VertexDataType, typename EdgeDataType>
class TraversalBase {
 public:

  // Virtual destructor
  virtual ~TraversalBase() {}

  // Begin handler
  virtual void begin() const = 0;

  // End handler
  virtual void end() const = 0;

  // Gray color handler
  virtual void paint_to_gray(int v) const = 0;

  // Black color handler
  virtual void paint_to_black(int v) const = 0;

  // Dump vector of colors
  virtual std::vector<int> operator () (const Graph<VertexDataType, EdgeDataType>& graph) const = 0;
};

template <typename VertexDataType, typename EdgeDataType>
class BFS : TraversalBase<VertexDataType, EdgeDataType> {
 public:

  std::vector<int> operator()(const Graph<VertexDataType, EdgeDataType>& graph) const override {

    std::vector<int> result(graph.vertices(), WHITE);

    begin();

    for (size_t v = 0; v < graph.vertices(); ++v) {
      if (result[v] == WHITE) {
        bfs(v, &result, graph);
      }
    }

    end();

    return result;
  }

  ~BFS() {};

 private:
  void begin() const override {
    std::cout << "Begin BFS" << std::endl;
  }

  void end() const override {
    std::cout << "End BFS" << std::endl << std::endl;
  }

  void paint_to_gray(int v) const override {
    std::cout << "Vertex " << v << " is gray now" << std::endl;
  }

  void paint_to_black(int v) const override {
    std::cout << "Vertex " << v << " is black now" << std::endl;
  }

  // breadth-first-search from vertex v
  void bfs(size_t v, std::vector<int> *result, const Graph<VertexDataType, EdgeDataType> &graph) const;
};

template <typename VertexDataType, typename EdgeDataType>
void BFS<VertexDataType, EdgeDataType>::bfs(size_t v, std::vector<int> *result, const Graph<VertexDataType, EdgeDataType> &graph) const {
  std::queue<int> queue;
  (*result)[v] = Colors::GRAY;
  paint_to_gray(v);
  queue.push(v);

  while (!queue.empty()) {
    int u = queue.front();

    for (int i = 0; i < graph.adjacent_lists_[u].size(); ++i) {
      int w = graph.adjacent_lists_[u][i].v_;

      if ((*result)[w] == Colors::WHITE) {

        (*result)[w] = Colors::GRAY;
        paint_to_gray(w);
        queue.push(w);
      }
    }

    (*result)[u] = Colors::BLACK;
    paint_to_black(u);
    queue.pop();
  }
};

template <typename VertexDataType, typename EdgeDataType>
class DFS : TraversalBase<VertexDataType, EdgeDataType> {
 public:

  // functor-style
  std::vector<int> operator()(const Graph<VertexDataType, EdgeDataType>& graph) const override {

    std::vector<int> result(graph.vertices(), WHITE);

    begin();

    for (size_t v = 0; v < graph.vertices(); ++v) {
      if (result[v] == WHITE) {
        dfs(v, &result, graph);
      }
    }

    end();

    return result;
  }

  ~DFS() {}

 private:
  void begin() const override {
    std::cout << "Begin DFS" << std::endl;
  }

  void end() const override {
    std::cout << "End DFS" << std::endl << std::endl;
  }

  void paint_to_gray(int v) const override {
    std::cout << "Vertex " << v << " is gray now" << std::endl;
  }

  void paint_to_black(int v) const override {
    std::cout << "Vertex " << v << " is black now" << std::endl;
  }

  // depth-first-search from vertex v
  void dfs(size_t v, std::vector<int> *result, const Graph<VertexDataType, EdgeDataType> &graph) const;

};

template <typename VertexDataType, typename EdgeDataType>
void DFS<VertexDataType, EdgeDataType>::dfs(size_t v, std::vector<int> *result, const Graph<VertexDataType, EdgeDataType> &graph) const {
  (*result)[v] = Colors::GRAY;
  paint_to_gray(v);

  for (size_t i = 0; i < graph.adjacent_lists_[v].size(); ++i) {
    int w = graph.adjacent_lists_[v][i].v_;
    if ((*result)[w] == Colors::WHITE) {
      dfs(w, result, graph);
    }
  }

  (*result)[v] = Colors::BLACK;
  paint_to_black(v);
};


#endif //GRAPH_TRAVERSER_TRAVERSAL_HPP
