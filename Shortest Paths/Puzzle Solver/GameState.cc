//
// Created by whoami on 10/11/16.
//

#include <cmath>

#include "GameState.h"

const int GameState::dx[4] = {0, 1, 0, -1};
const int GameState::dy[4] = {1, 0, -1, 0};
const char GameState::direction[4] = {'R', 'D', 'L', 'U'};

GameState::GameState(const Table& state)
  : size_(state.size()), priority_(0) {
    hash_value_ = 0;
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        hash_value_ += static_cast<hash_t>(state[i][j]) *
            static_cast<hash_t>(pow(size_ * size_, size_ * i + j));
      }
    }
}

Table GameState::GetFinalState(size_t size) {
  Table result(size, std::vector<int>(size));

  for (int i = 0; i < result.size(); ++i) {
    for (int j = 0; j < result.size(); ++j) {
      result[i][j] = static_cast<int>(((size * i + j + 1) % (size * size)));
    }
  }

  return result;
}

std::vector<std::pair<GameState, int>> GameState::GetAdjacent() const {
  std::vector<std::pair<GameState, int>> result;

  Table state = GetGameState();

  // Searching for a missing tile in the state
  int zero_x = -1, zero_y = -1;
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (state[i][j] == 0) {
        zero_x = i;
        zero_y = j;
        break;
      }
    }
  }

  // Looking for correct adjacent moves
  for (int move = 0; move < 4; ++move) {
    if (CheckAdjacent(zero_x + dx[move], zero_y + dy[move], size_)) {
      std::swap(state[zero_x][zero_y], state[zero_x + dx[move]][zero_y + dy[move]]);

      result.push_back(std::make_pair(GameState(size_, GetHashValueByGameState(state)), move));

      std::swap(state[zero_x][zero_y], state[zero_x + dx[move]][zero_y + dy[move]]);
    }
  }

  return result;
}

hash_t GameState::GetHashValueByGameState(const Table& state) {
  hash_t result = 0;

  // Iterating over the state and calculating hash value
  for (int i = 0; i < state.size(); ++i) {
    for (int j = 0; j < state.size(); ++j) {
      result += static_cast<hash_t>(state[i][j]) *
                static_cast<hash_t>(pow(state.size() * state.size(), state.size() * i + j));
    }
  }

  return result;
}

Table GameState::GetGameStateByHashValue(size_t size, hash_t hashvalue) {
  Table result(size, std::vector<int>(size));

  // Restoring state with the help of given hash value
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result[i][j] = static_cast<int>(hashvalue % (size * size));
      hashvalue /= size * size;
    }
  }

  return result;
}

