//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_PUZZLESOLVER_H
#define B_PUZZLE_SOLVER_PUZZLESOLVER_H

#include <string>

#include "GameState.h"

// Main logic class
// Provides the interface to solve a sliding puzzle
// Based on A* family algorithms
class PuzzleSolver {
 public:
  // Default constructor
  PuzzleSolver() {}

  // Custom constructor
  explicit PuzzleSolver(GameState start_state)
      : start_state_(start_state) {}

  // Returns the fact solution exists
  std::string GetFeasibilityOfSolution() {
    if (!estimated_feasibility_) {
      solution_exists_ = CheckIfSolutionExists();
      estimated_feasibility_ = true;
    }

    return solution_exists_ ? "YES" : "NO";
  }

  // Returns the sequence which is the shortest way to solve problem
  std::string GetAnswerSequence() {
    if (!found_answer_) {
      answer_sequence_ = FindAnswerSequence();
      found_answer_ = true;
    }

    return answer_sequence_;
  }

 private:
  // Finds the shortest way to solve a puzzle
  std::string FindAnswerSequence();

  // Testify existence of solution
  bool CheckIfSolutionExists();

  bool solution_exists_ = false;
  bool estimated_feasibility_ = false;
  bool found_answer_ = false;

  std::string answer_sequence_;

  GameState start_state_;
};

#endif //B_PUZZLE_SOLVER_PUZZLESOLVER_H
