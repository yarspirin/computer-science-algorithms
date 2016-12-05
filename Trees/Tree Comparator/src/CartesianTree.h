//
// Created by whoami on 12/5/16.
//

#ifndef TREE_COMPARATOR_CARTESIANTREE_H
#define TREE_COMPARATOR_CARTESIANTREE_H

#include <memory>

class CartesianTree {
 public:
  CartesianTree()
      : root_(nullptr) { }

  void Put(int key, int priority);
  bool Contains(int key) const;
  void Traverse(std::ostream& output_stream) const;
  int GetHeight() const;
  int GetWidth() const;

 private:
  struct CTNode {
    CTNode(int _key, int _priority)
        : key(_key),
          priority(_priority),
          left(nullptr),
          right(nullptr) { }

    int key;
    int priority;

    std::unique_ptr<CTNode> left;
    std::unique_ptr<CTNode> right;
  };

  static std::unique_ptr<CTNode>& Merge(std::unique_ptr<CTNode>& left, std::unique_ptr<CTNode>& right);
  static std::pair<std::unique_ptr<CTNode>, std::unique_ptr<CTNode>> Split(std::unique_ptr<CTNode>& node, int key);

  bool ContainsAtNode(int key, std::unique_ptr<CTNode>& node) const;
  void TraverseAtNode(std::ostream& output_stream, std::unique_ptr<CTNode>& node) const;
  int GetHeightOfNode(std::unique_ptr<CTNode>& node) const;

  std::unique_ptr<CTNode> root_;
};


#endif //TREE_COMPARATOR_CARTESIANTREE_H
