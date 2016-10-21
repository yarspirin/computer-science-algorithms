//
//  main.cpp
//  Puzzle Solver
//
//  Created by whoami on 10/3/16.
//  Copyright © 2016 Mountain Viewer. All rights reserved.
//

// The provided code finds the shortest solution for a sliding puzzle
// It works well with all tables which size are < 5

#include <iostream>
#include <vector>
#include <fstream>

#include "GameState.h"
#include "PuzzleSolver.h"

const std::string input_filename = "puzzle.in";
const std::string output_filename = "puzzle.out";

// Execution
void run() {
  // std::ifstream in(input_filename);
  // std::ofstream out(output_filename);

  int size = 0;
  std::cin >> size;

  Table start_state(static_cast<size_t>(size), std::vector<int>(static_cast<size_t>(size)));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cin >> start_state[i][j];
    }
  }

  GameState start(start_state);

  PuzzleSolver solver(start);

  std::cout << solver.GetFeasibilityOfSolution() << std::endl;
  std::cout << solver.GetAnswerSequence().size() << std::endl;
  std::cout << solver.GetAnswerSequence() << std::endl;
}

int main(int argc, const char * argv[]) {
  run();
  return 0;
}
