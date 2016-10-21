//
// Created by whoami on 10/11/16.
//

#include <set>
#include <map>
#include <queue>

#include "PuzzleSolver.h"
#include "CoveredCost.h"
#include "ManhattanHeuristic.h"

// Math approach to testify feasibility
// Based on properties of permutations
bool PuzzleSolver::CheckIfSolutionExists() {
  Table state = start_state_.GetGameState();
  std::vector<int> permutation;

  int zero_row = -1;

  for (int i = 0; i < state.size(); ++i) {
    for (int j = 0; j < state.size(); ++j) {
      if (state[i][j] == 0) {
        zero_row = i;
        continue;
      }
      permutation.push_back(state[i][j]);
    }
  }

  int num_inversions = 0;
  for (int i = 0; i < permutation.size() - 1; ++i) {
    for (int j = i + 1; j < permutation.size(); ++j) {
      if (permutation[i] > permutation[j]) {
        num_inversions += 1;
      }
    }
  }

  if (start_state_.GetSize() % 2 == 1) {
    return num_inversions % 2 == 0;
  }

  return (num_inversions % 2 == 0) ^ (zero_row % 2 == 0);
}

std::string PuzzleSolver::FindAnswerSequence() {
  if (!estimated_feasibility_) {
    solution_exists_ = CheckIfSolutionExists();
    estimated_feasibility_ = true;
  }

  // Returns empty sequence
  if (!solution_exists_) {
    return answer_sequence_;
  }

  // Keeping track of used states
  std::set<GameState> visited_states;

  // Storage of priorities and moves for game states
  std::map<GameState, GameStateInfo> priorities;

  // States opened at the moment
  std::priority_queue<GameState, std::vector<GameState>, GameStateComparator> pending_states((GameStateComparator()));
  std::set<GameState> in_the_queue;

  // Functor instances
  CoveredCost cost_function;
  ManhattanHeuristic heuristic_function;

  // Initial state
  pending_states.push(start_state_);
  in_the_queue.insert(start_state_);
  priorities[start_state_] = GameStateInfo(cost_function(start_state_) + 0 + heuristic_function(start_state_),
                                           0, '\0', -1);

  start_state_.SetPriority(cost_function(start_state_) + 0 + heuristic_function(start_state_));

  // Final state
  GameState expected_game_state(GameState::GetFinalState(start_state_.GetSize()));

  // Work already done, just return nothing
  if (start_state_ == expected_game_state) {
    return "";
  }

  while (!pending_states.empty()) {
    // Extracting the optimal state
    GameState current_state = pending_states.top();

    // Found terminal state
    if (current_state == expected_game_state) {
      break;
    }

    pending_states.pop();
    in_the_queue.erase(current_state);
    visited_states.insert(current_state);

    // Iterating over adjacent states
    std::vector<std::pair<GameState, int>> adjacent_states = current_state.GetAdjacent();
    for (auto& state_pair : adjacent_states) {
      // Getting state and move direction from previous state
      GameState state = state_pair.first;
      int move = state_pair.second;

      // Number of covered states
      int new_covered = priorities[current_state].GetCovered() + 1;

      if (visited_states.find(state) == visited_states.end() || new_covered < priorities[state].GetCovered()) {
        // Calculating the state properties
        priorities.erase(state);
        priorities[state] = GameStateInfo(cost_function(state) + new_covered + heuristic_function(state),
                                          new_covered,
                                          GameState::direction[move],
                                          current_state.GetHash());

        state.SetPriority(cost_function(state) + new_covered + heuristic_function(state));

        if (in_the_queue.find(state) == in_the_queue.end()) {
	  in_the_queue.insert(state);
          pending_states.push(state);
        }
      }
    }
  }

  // Restoring answer which will be given in reverse order
  std::string result;
  while (priorities[expected_game_state].GetMove() != '\0') {
    result += priorities[expected_game_state].GetMove();
    expected_game_state = GameState(
        GameState::GetGameStateByHashValue(start_state_.GetSize(),
                                           priorities[expected_game_state].GetPreviousHash())
    );
  }

  std::reverse(result.begin(), result.end());
  return result;
}
