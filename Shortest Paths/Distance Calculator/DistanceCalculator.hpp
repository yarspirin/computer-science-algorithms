//
// Created by whoami on 10/11/16.
//

#ifndef C_DISTANCE_CALCULATOR_DISTANCECALCULATOR_HPP
#define C_DISTANCE_CALCULATOR_DISTANCECALCULATOR_HPP

#include "GraphStorageFactory.hpp"

// Main logic class
// Provide an interface to calculate the shortest paths in a graph
template<class InputStreamType>
class DistanceCalculator {
 public:
  DistanceCalculator() { }

  // Creating graph storage object with the help of the factory class
  DistanceCalculator(InputStreamType &input_stream) {
    graph_storage_ = *(GraphStorageFactory<InputStreamType>::BuildFromStream(input_stream));
  }

  // Processing the shortest ways from any vertex to any other (based on Floyd algorithm)
  DistanceMatrix ProcessFloydAlgorithm() {
    DistanceMatrix distances = graph_storage_.graph_matrix;

    for (int k = 0; k < graph_storage_.num_vertices; ++k) {
      for (int i = 0; i < graph_storage_.num_vertices; ++i) {
        for (int j = 0; j < graph_storage_.num_vertices; ++j) {
          distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
        }
      }
    }

    return distances;
  }

 private:
  GraphStorage graph_storage_;
};


#endif //C_DISTANCE_CALCULATOR_DISTANCECALCULATOR_HPP
