//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_HEURISTICINTERFACE_H
#define B_PUZZLE_SOLVER_HEURISTICINTERFACE_H

#include "GameState.h"

// Heuristics can be derived from the HeuristicInterface
class HeuristicInterface {
 public:
  virtual int operator () (const GameState& game_state) = 0;
};


#endif //B_PUZZLE_SOLVER_HEURISTICINTERFACE_H
