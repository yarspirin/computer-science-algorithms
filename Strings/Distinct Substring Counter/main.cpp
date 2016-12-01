#include <iostream>

#include "DistinctSubstringCounter.h"

// Execution
void run() {
  std::string str;
  std::cin >> str;

  DistinctSubstringCounter distinct_substring_counter(str);
  std::cout << distinct_substring_counter.GetNumberOfDistinctSubstrings() << std::endl;
}

int main() {
  run();
  return 0;
}