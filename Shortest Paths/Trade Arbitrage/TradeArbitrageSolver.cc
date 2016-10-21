//
// Created by whoami on 10/11/16.
//

#include "TradeArbitrageSolver.h"

void TradeArbitrageSolver::InitSolver(const ExchangeMatrix &exchange_courses) {
  for (int i = 0; i < num_currencies_; ++i) {
    for (int j = 0; j < num_currencies_; ++j) {

      // Loops are meaningless like the edges that do not exist
      if (exchange_courses[i][j] == -1 || i == j) {
        continue;
      }

      // Using "-log" values to convert product to sum and then find negative cycle
      exchanges_.push_back(Course(i, j, -log(exchange_courses[i][j])));
    }
  }

  // Additional vertex that is a source
  // Used to make any cycle reachable from the vertex
  for (int i = 0; i < num_currencies_; ++i) {
    exchanges_.push_back(Course(num_currencies_, i, 0.0));
  }

  num_currencies_ += 1;
}

std::string TradeArbitrageSolver::FindArbitrage() const {
  std::vector<double> course_exchange(static_cast<size_t>(num_currencies_), kINF);
  course_exchange[num_currencies_ - 1] = 0.0;

  bool made_relaxation = false;

  for (int iter = 0; iter < num_currencies_; ++iter) {
    made_relaxation = false;

    for (auto& exchange : exchanges_) {

      // If vertex haven't been visited
      if (course_exchange[exchange.from] == kINF) {
        continue;
      }

      // Relaxation, avoid large negative values in
      if (course_exchange[exchange.from] + exchange.course_value < course_exchange[exchange.to]) {
        course_exchange[exchange.to] = std::max(-kINF, course_exchange[exchange.from] + exchange.course_value);
        made_relaxation = true;
      }
    }
  }

  return made_relaxation ? "YES" : "NO";
}