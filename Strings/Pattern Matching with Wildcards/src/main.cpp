#include <iostream>
#include <unordered_map>
#include <queue>

#include "Solver.h"

// Execution
void run() {
  std::string pattern;
  std::cin >> pattern;

  std::string text;
  std::cin >> text;

  Solver solver(pattern, text);
  solver.Init();
  std::vector<int> entries = solver.GetEntries();

  for (auto& entry : entries) {
    std::cout << entry << " ";
  }
  std::cout << std::endl;
}

int main() {
  run();
  return 0;
}