#include <iostream>
#include <vector>

#include "SegmentTree.h"

void run() {
  int array_size = 0, num_queries = 0;

  std::cin >> array_size >> num_queries;

  std::vector<int> array(array_size);

  for (int i = 0; i < array_size; ++i) {
    std::cin >> array[i];
  }

  SegmentTree segment_tree;
  segment_tree.BuildTree(array);

  for (int query = 0; query < num_queries; ++query) {
    int left_query = 0, right_query = 0;
    std::cin >> left_query >> right_query;
    std::cout << segment_tree.GetSecondStatistics(left_query - 1, right_query - 1) << std::endl;
  }
}

int main() {
  run();
  return 0;
}