//
// Created by whoami on 10/11/16.
//

#include <iostream>
#include "TradeArbitrageSolver.h"

// Execution
void run() {
  int num_currencies = 0;
  std::cin >> num_currencies;

  ExchangeMatrix exchanges(static_cast<size_t>(num_currencies),
                            std::vector<double>(static_cast<size_t>(num_currencies), 1));

  for (int i = 0; i < num_currencies; ++i) {
    for (int j = 0; j < num_currencies; ++j) {

      if (i == j) {
        continue;
      }

      std::cin >> exchanges[i][j];
    }
  }

  TradeArbitrageSolver solver(num_currencies);
  solver.InitSolver(exchanges);

  std::cout << solver.FindArbitrage() << std::endl;
}

// Application entry point
// Delegates the whole work to other resources
int main(int argc, const char * argv[]) {
  run();
  return 0;
}