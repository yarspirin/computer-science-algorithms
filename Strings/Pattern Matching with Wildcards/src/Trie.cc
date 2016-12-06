//
// Created by whoami on 12/1/16.
//

#include <string>

#include "Trie.h"

bool Trie::ContainsAtNode(const std::string &sample, int pos, std::shared_ptr<Node>& node) {
  if (pos == sample.length()) {
    return node->is_leaf;
  }

  if (node->children.find(sample[pos]) == node->children.end()) {
    return false;
  }

  return ContainsAtNode(sample, pos + 1, node->children[sample[pos]]);
}

bool Trie::Contains(const std::string &sample) {
  return ContainsAtNode(sample, 0, root_);
}

void Trie::PutAtNode(const std::string &sample, int pos, std::shared_ptr<Node>& node, int id) {
  if (pos == sample.length()) {
    node->is_leaf = true;
    node->ids.push_back(id);
    return;
  }

  if (node->children.find(sample[pos]) == node->children.end()) {
    node->children[sample[pos]] = std::make_shared<Node>(Node(node));
  }

  PutAtNode(sample, pos + 1, node->children[sample[pos]], id);
}

void Trie::Put(const std::string &sample, int id) {
  PutAtNode(sample, 0, root_, id);
}
