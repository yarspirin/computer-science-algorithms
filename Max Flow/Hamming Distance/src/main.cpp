#include <iostream>
#include <vector>
#include <queue>

#include "Solver.h"

// Execution
void run() {
  std::string origin;
  std::string pattern;

  std::cin >> origin;
  std::cin >> pattern;

  Solver solver(origin, pattern);
  solver.Init();

  std::cout << solver.FindMaxCorrelation() << std::endl;

  std::pair<std::string, std::string> ans = solver.RetrieveTemplates();
  std::cout << ans.first << std::endl;
  std::cout << ans.second << std::endl;
}

int main() {
  run();
  return 0;
}