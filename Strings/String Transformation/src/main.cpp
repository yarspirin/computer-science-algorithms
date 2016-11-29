#include <iostream>
#include <vector>
#include <sstream>

#include "Transformer.h"

// Execution
void run() {
  std::string input;
  std::getline(std::cin, input);

  std::stringstream stream(input);
  int value = 0;

  std::vector<int> values;
  while (stream >> value) {
    values.push_back(value);
  }

  Transformer transformer;

  std::cout << transformer.TransformByPrefixValues(values) << std::endl;
  std::cout << transformer.TransformByZValues(values) << std::endl;
}

int main() {
  run();
  return 0;
}