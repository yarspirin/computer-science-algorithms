//
// Created by whoami on 10/11/16.
//

#ifndef C_DISTANCE_CALCULATOR_GRAPHSTORAGEFACTORY_HPP
#define C_DISTANCE_CALCULATOR_GRAPHSTORAGEFACTORY_HPP

#include <vector>
#include <memory>

// Type alias to make shorter and clearer code
using DistanceMatrix = std::vector<std::vector<int>>;

// GraphStorage instances store graph data
struct GraphStorage {

  GraphStorage() { }

  GraphStorage(int _num_vertices, const DistanceMatrix &_graph_matrix)
      : num_vertices(_num_vertices), graph_matrix(_graph_matrix) { }

  int num_vertices;
  DistanceMatrix graph_matrix;
};

// GraphStorageFactory builds instances of GraphStorage class
template<class InputStreamType>
class GraphStorageFactory {
 public:
  // Preventing usage of constructor and destructor
  GraphStorageFactory() = delete;
  ~GraphStorageFactory() = delete;

  // Factory method
  static std::unique_ptr<GraphStorage> BuildFromStream(InputStreamType &input_stream) {
    int num_vertices = 0;
    input_stream >> num_vertices;

    DistanceMatrix graph_matrix(static_cast<size_t>(num_vertices),
                                 std::vector<int>(static_cast<size_t>(num_vertices)));

    for (int i = 0; i < num_vertices; ++i) {
      for (int j = 0; j < num_vertices; ++j) {
        input_stream >> graph_matrix[i][j];
      }
    }

    return std::make_unique<GraphStorage>(num_vertices, graph_matrix);
  }
};


#endif //C_DISTANCE_CALCULATOR_GRAPHSTORAGEFACTORY_HPP
