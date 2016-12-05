//
// Created by whoami on 12/5/16.
//

#include <unordered_map>
#include <queue>
#include <ostream>

#include "CartesianTree.h"

int CartesianTree::GetWidth() const {
  if (!root_) {
    return 0;
  }

  // level: key -> height in tree
  std::unordered_map<int, int> level;
  std::queue<CTNode*> queue;

  level[root_->key] = 0;
  queue.push(root_.get());

  while (!queue.empty()) {
    CTNode* front = queue.front();
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

int CartesianTree::GetHeight() const {
  if (!root_) {
    return 0;
  }

  return std::max(GetHeightOfNode(root_->left), GetHeightOfNode(root_->right)) + 1;
}

int CartesianTree::GetHeightOfNode(std::unique_ptr<CTNode> &node) const {
  if (!node) {
    return 0;
  }

  return std::max(GetHeightOfNode(node->left), GetHeightOfNode(node->right)) + 1;
}

bool CartesianTree::Contains(int key) const {
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

bool CartesianTree::ContainsAtNode(int key, std::unique_ptr<CTNode> &node) const {
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

void CartesianTree::Traverse(std::ostream &output_stream) const {
  if (!root_) {
    return;
  }

  TraverseAtNode(output_stream, root_->left);
  output_stream << root_->key << " ";
  TraverseAtNode(output_stream, root_->right);
  output_stream << std::endl;
}

void CartesianTree::TraverseAtNode(std::ostream &output_stream, std::unique_ptr<CTNode> &node) const {
  if (!node) {
    return;
  }

  TraverseAtNode(output_stream, node->left);
  output_stream << node->key << " ";
  TraverseAtNode(output_stream, node->right);
}

std::unique_ptr<CartesianTree::CTNode>& CartesianTree::Merge(std::unique_ptr<CTNode> &left,
                                                             std::unique_ptr<CTNode> &right) {
  if (!left) {
    return right;
  }

  if (!right) {
    return left;
  }

  if (left->priority > right->priority) {
    left->right = std::move(Merge(left->right, right));
    return left;
  } else {
    right->left = std::move(Merge(left, right->left));
    return right;
  }
}

std::pair<std::unique_ptr<CartesianTree::CTNode>, std::unique_ptr<CartesianTree::CTNode>>
CartesianTree::Split(std::unique_ptr<CTNode> &node, int key) {
  if (!node) {
    return std::make_pair(nullptr, nullptr);
  }

  if (key > node->key) {
    std::pair<std::unique_ptr<CTNode>, std::unique_ptr<CTNode>> result = Split(node->right, key);
    node->right = std::move(result.first);
    return std::make_pair(std::move(node), std::move(result.second));
  } else {
    std::pair<std::unique_ptr<CTNode>, std::unique_ptr<CTNode>> result = Split(node->left, key);
    node->left = std::move(result.second);
    return std::make_pair(std::move(result.first), std::move(node));
  }
}

void CartesianTree::Put(int key, int priority) {
  if (Contains(key)) {
    return;
  }

  std::pair<std::unique_ptr<CTNode>, std::unique_ptr<CTNode>> result = Split(root_, key);
  std::unique_ptr<CTNode> added_node = std::make_unique<CTNode>(CTNode(key, priority));
  result.first = std::move(Merge(result.first, added_node));
  root_ = std::move(Merge(result.first, result.second));
}
