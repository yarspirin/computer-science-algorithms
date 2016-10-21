//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_COVEREDCOST_H
#define B_PUZZLE_SOLVER_COVEREDCOST_H

#include "CostInterface.h"

// Covered cost addition implementation
class CoveredCost : public CostInterface {
 public:
  virtual int operator () (const GameState& game_state);
};

#endif //B_PUZZLE_SOLVER_COVEREDCOST_H
