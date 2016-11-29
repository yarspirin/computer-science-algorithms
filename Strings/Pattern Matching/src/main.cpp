#include <iostream>

#include "PatternMatcher.h"

// Execution
void run() {
  std::string pattern;
  std::string text;

  std::cin >> pattern >> text;

  PatternMatcher pattern_matcher(pattern, text);

  pattern_matcher.DumpEntries();
}

int main() {
  run();
  return 0;
}