
#include <iostream>
#include <vector>
#include <fstream>

#include "DistanceCalculator.hpp"

const std::string input_filename = "floyd.in";
const std::string output_filename = "floyd.out";

// Execution
void run() {

  // std::ifstream in(input_filename);
  // std::ofstream out(output_filename);

  DistanceCalculator<std::istream> distance_calculator(std::cin);

  DistanceMatrix calculated_matrix = distance_calculator.ProcessFloydAlgorithm();

  for (int i = 0; i < calculated_matrix.size(); ++i) {
    for (int j = 0; j < calculated_matrix.size(); ++j) {
      std::cout << calculated_matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, const char * argv[]) {
  run();
  return 0;
}
