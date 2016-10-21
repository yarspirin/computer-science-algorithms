//
// Created by whoami on 10/11/16.
//

#include <cstdlib>

#include "ManhattanHeuristic.h"

int ManhattanHeuristic::operator () (const GameState& game_state) {
  int distance = 0;

  Table state = game_state.GetGameState();

  size_t size = state.size();

  for (int i = 0; i < state.size(); ++i) {
    for (int j = 0; j < state.size(); ++j) {
      if (state[i][j] == 0) {
        distance += abs(i - static_cast<int>(size) + 1) + abs(j - static_cast<int>(size) + 1);
      } else {
        distance += abs(i - static_cast<int>((state[i][j] - 1) / size)) +
                    abs(j - static_cast<int>((state[i][j] - 1) % size));
      }
    }
  }

  return distance;
}