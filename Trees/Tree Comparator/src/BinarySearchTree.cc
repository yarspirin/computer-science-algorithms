//
// Created by whoami on 12/5/16.
//

#include <unordered_map>
#include <queue>
#include <ostream>

#include "BinarySearchTree.h"


int BinarySearchTree::GetWidth() const {
  if (!root_) {
    return 0;
  }

  // level: key -> height in tree
  std::unordered_map<int, int> level;
  std::queue<BSTNode*> queue;

  level[root_->key] = 0;
  queue.push(root_.get());

  while (!queue.empty()) {
    BSTNode* front = queue.front();
    queue.pop();

    if (front->left) {
      level[front->left->key] = level[front->key] + 1;
      queue.push(front->left.get());
    }

    if (front->right) {
      level[front->right->key] = level[front->key] + 1;
      queue.push(front->right.get());
    }
  }

  int num_levels = 0;
  for (auto& entry : level) {
    if (num_levels < entry.second + 1) {
      num_levels = entry.second + 1;
    }
  }

  std::vector<int> width(static_cast<size_t>(num_levels));
  for (auto& entry : level) {
    width[entry.second] += 1;
  }

  return *std::max_element(width.begin(), width.end());
}

void BinarySearchTree::Put(int key) {
  if (!root_) {
    root_ = std::make_unique<BSTNode>(BSTNode(key));
    return;
  }

  if (key < root_->key) {
    PutAtNode(key, root_->left);
  } else if (key > root_->key) {
    PutAtNode(key, root_->right);
  }
}

bool BinarySearchTree::Contains(int key) const {
  if (!root_) {
    return false;
  }

  if (key == root_->key) {
    return true;
  } else if (key < root_->key) {
    return ContainsAtNode(key, root_->left);
  } else if (key > root_->key) {
    return ContainsAtNode(key, root_->right);
  }

  // Unreachable code
  return false;
}

void BinarySearchTree::Traverse(std::ostream& output_stream) const {
  if (!root_) {
    return;
  }

  TraverseAtNode(output_stream, root_->left);
  output_stream << root_->key << " ";
  TraverseAtNode(output_stream, root_->right);
  output_stream << std::endl;
}

int BinarySearchTree::GetHeight() const {
  if (!root_) {
    return 0;
  }

  return std::max(GetHeightOfNode(root_->left), GetHeightOfNode(root_->right)) + 1;
}

void BinarySearchTree::PutAtNode(int key, std::unique_ptr<BSTNode> &node) {
  if (!node) {
    node = std::make_unique<BSTNode>(BSTNode(key));
    return;
  }

  if (key < node->key) {
    PutAtNode(key, node->left);
  } else if (key > node->key) {
    PutAtNode(key, node->right);
  }
}

bool BinarySearchTree::ContainsAtNode(int key, std::unique_ptr<BSTNode> &node) const {
  if (!node) {
    return false;
  }

  if (key == node->key) {
    return true;
  } else if (key < node->key) {
    return ContainsAtNode(key, node->left);
  } else if (key > node->key) {
    return ContainsAtNode(key, node->right);
  }

  // Unreachable code
  return false;
}

void BinarySearchTree::TraverseAtNode(std::ostream &output_stream, std::unique_ptr<BSTNode> &node) const {
  if (!node) {
    return;
  }

  TraverseAtNode(output_stream, node->left);
  output_stream << node->key << " ";
  TraverseAtNode(output_stream, node->right);
}

int BinarySearchTree::GetHeightOfNode(std::unique_ptr<BSTNode> &node) const {
  if (!node) {
    return 0;
  }

  return std::max(GetHeightOfNode(node->left), GetHeightOfNode(node->right)) + 1;
}
