//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_COSTINTERFACE_H
#define B_PUZZLE_SOLVER_COSTINTERFACE_H

#include "GameState.h"

// Cost functions can be derived from the CostInterface
struct CostInterface {
 public:
  virtual int operator () (const GameState& game_state) = 0;
};

#endif //B_PUZZLE_SOLVER_COSTINTERFACE_H
