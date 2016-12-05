//
// Created by whoami on 12/5/16.
//

#ifndef TREE_COMPARATOR_BINARYSEARCHTREE_H
#define TREE_COMPARATOR_BINARYSEARCHTREE_H

#include <memory>

class BinarySearchTree {
 public:
  BinarySearchTree()
      : root_(nullptr) { }

  void Put(int key);
  bool Contains(int key) const;
  void Traverse(std::ostream& output_stream) const;
  int GetHeight() const;
  int GetWidth() const;

 private:
  struct BSTNode {
    BSTNode(int _key)
        : key(_key),
          left(nullptr),
          right(nullptr) { }

    int key;

    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;
  };

  void PutAtNode(int key, std::unique_ptr<BSTNode>& node);
  bool ContainsAtNode(int key, std::unique_ptr<BSTNode>& node) const;
  void TraverseAtNode(std::ostream& output_stream, std::unique_ptr<BSTNode>& node) const;
  int GetHeightOfNode(std::unique_ptr<BSTNode>& node) const;

  std::unique_ptr<BSTNode> root_;
};


#endif //TREE_COMPARATOR_BINARYSEARCHTREE_H
