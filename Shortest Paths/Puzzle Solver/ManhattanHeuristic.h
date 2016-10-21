//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_MANHATTANHEURISTIC_H
#define B_PUZZLE_SOLVER_MANHATTANHEURISTIC_H

#include "HeuristicInterface.h"

// Manhattan heuristic implementation
class ManhattanHeuristic : public HeuristicInterface {
 public:
  int operator () (const GameState& game_state);
};

#endif //B_PUZZLE_SOLVER_MANHATTANHEURISTIC_H
