//
// Created by whoami on 10/11/16.
//

#ifndef B_PUZZLE_SOLVER_GAMESTATE_H
#define B_PUZZLE_SOLVER_GAMESTATE_H

#include <cstdint>
#include <vector>

using hash_t = int64_t;
using Table = std::vector<std::vector<int>>;

// GameState instances store hashes of game states to reduce memory usage
// Hashes are unique, so it is easy to restore game state back
class GameState {
 public:
  // Default constructor
  GameState() : size_(0), hash_value_(-1), priority_(0) {}

  // Custom constructor, applying hash value that was already calculated
  GameState(size_t size, hash_t hash_value)
      : size_(size), hash_value_(hash_value), priority_(0) {}

  // Custom constructor, calculating hash value from state
  explicit GameState(const Table& state);

  // Operators for handy work with states
  bool operator == (const GameState& other_state) const {
    return hash_value_ == other_state.hash_value_;
  }

  bool operator != (const GameState& other_state) const {
    return hash_value_ != other_state.hash_value_;
  }

  bool operator < (const GameState& other_state) const {
    return hash_value_ < other_state.hash_value_;
  }

  // Get state by hash value
  static Table GetGameStateByHashValue(size_t size, hash_t hash_value);

  // Get the self state
  Table GetGameState() const {
    return GetGameStateByHashValue(size_, hash_value_);
  }

  // Get states which are adjacent to this
  std::vector<std::pair<GameState, int>> GetAdjacent() const;

  // Get the size of state
  size_t GetSize() const {
    return size_;
  }

  // Get the hash value
  hash_t GetHash() const {
    return hash_value_;
  }

  // Final destination
  static Table GetFinalState(size_t size);

  // Access to state priorities
  void SetPriority(int priority) {
    priority_ = priority;
  }

  int GetPriority() const {
    return priority_;
  }

  // All posible moves
  static const char direction[4];

 private:
  // Check if position is correct
  static bool CheckAdjacent(int pos_x, int pos_y, size_t size) {
    return 0 <= pos_x && 0 <= pos_y && pos_x < size && pos_y < size;
  }

  // Get hash value by state
  static hash_t GetHashValueByGameState(const Table& state);

  // All possible moves
  static const int dx[4];
  static const int dy[4];

  int priority_;
  size_t size_;
  hash_t hash_value_;
};

// Provide additional info for game states
class GameStateInfo {
 public:
  GameStateInfo() {}

  GameStateInfo(int priority, int covered, char move, hash_t previous_hash)
      : priority_(priority), covered_(covered),
        move_(move), previous_hash_(previous_hash) {}

  int GetPriority() const {
    return priority_;
  }

  int GetCovered() const {
    return covered_;
  }

  char GetMove() const {
    return move_;
  }

  hash_t GetPreviousHash() const {
    return previous_hash_;
  }

 private:
  int priority_;
  int covered_;
  char move_;
  hash_t previous_hash_;
};

// Comparator for maintenance game states in priority queue
struct GameStateComparator {
 public:
  bool operator () (const GameState& left, const GameState& right) {
    return left.GetPriority() > right.GetPriority();
  }
};

#endif //B_PUZZLE_SOLVER_GAMESTATE_H
