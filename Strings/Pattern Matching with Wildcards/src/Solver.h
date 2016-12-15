//
// Created by whoami on 12/1/16.
//

#ifndef PATTERN_MATCHING_WITH_QUESTION_MARKS_SOLVER_H
#define PATTERN_MATCHING_WITH_QUESTION_MARKS_SOLVER_H

#include <vector>

#include "DeterministicFiniteAutomaton.h"

// Process and return all occurrences of a given pattern with wildcards in a given text
class Solver {
 public:
  Solver(const std::string& pattern, const std::string& text);
  std::vector<int> GetEntries();

 private:
  std::vector<std::pair<int, int>> GetIndices();

  // All parts presented in a way [begin, end]
  std::vector<std::pair<int, int>> indices_;

  int pattern_begin_, pattern_end_;
  int text_begin_, text_end_;

  std::string pattern_;
  std::string text_;

  DeterministicFiniteAutomaton dfa_;
};


#endif //PATTERN_MATCHING_WITH_QUESTION_MARKS_SOLVER_H
