#include <iostream>
#include <vector>

#include "BinarySearchTree.h"
#include "CartesianTree.h"

struct Key {
  Key(int _x = 0, int _y = 0)
      : x(_x), y(_y) { }

  int x;
  int y;
};

void run() {
  int num_keys = 0;
  std::cin >> num_keys;

  std::vector<Key> keys(static_cast<size_t>(num_keys));
  for (int i = 0; i < num_keys; ++i) {
    int x = 0, y = 0;
    std::cin >> x >> y;
    keys[i] = Key(x, y);
  }

  BinarySearchTree binary_search_tree;
  for (auto& key : keys) {
    binary_search_tree.Put(key.x);
  }
  binary_search_tree.Traverse(std::cout);

  CartesianTree cartesian_tree;
  for (auto& key : keys) {
    cartesian_tree.Put(key.x, key.y);
  }
  cartesian_tree.Traverse(std::cout);

  std::cout << cartesian_tree.GetWidth() - binary_search_tree.GetWidth() << std::endl;
  std::cout << binary_search_tree.GetHeight() - cartesian_tree.GetHeight() << std::endl;
}

int main() {
  run();
  return 0;
}