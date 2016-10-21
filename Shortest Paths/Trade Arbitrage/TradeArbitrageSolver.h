//
// Created by whoami on 10/11/16.
//

#ifndef A_TRADE_ARBITRAGE_TRADEARBITRAGESOLVER_H
#define A_TRADE_ARBITRAGE_TRADEARBITRAGESOLVER_H

#include <vector>
#include <cmath>
#include <string>

// Type alias to make shorter and clearer code
using ExchangeMatrix = std::vector<std::vector<double>>;

// Double infinity
const double kINF = 1e5;

// Course instances store info about exchanges
struct Course {
  Course() : from(-1), to(-1), course_value(0.0) { }

  Course(int _from, int _to, double _course_value)
      : from(_from), to(_to), course_value(_course_value) { }

  int from, to;
  double course_value;
};

// Main logic class
// Based on Ford-Bellman algorithm
class TradeArbitrageSolver {
 public:
  TradeArbitrageSolver() { }

  // Constructs by given number of currencies
  explicit TradeArbitrageSolver(int num_currencies)
      : num_currencies_(num_currencies) { }

  // Avoiding large constructor declarations
  void InitSolver(const ExchangeMatrix &exchange_courses);

  // Checks if there is an arbitrage
  // Outputs "YES" or "NO" as a result
  std::string FindArbitrage() const;

 private:
  int num_currencies_;
  std::vector<Course> exchanges_;
};


#endif //A_TRADE_ARBITRAGE_TRADEARBITRAGESOLVER_H
