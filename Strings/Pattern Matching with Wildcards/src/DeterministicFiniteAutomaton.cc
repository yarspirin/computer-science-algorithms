//
// Created by whoami on 12/1/16.
//

#include <queue>
#include <cassert>
#include <iostream>

#include "DeterministicFiniteAutomaton.h"


std::shared_ptr<Node>& DeterministicFiniteAutomaton::GetRoot() {
  return root_;
}

std::shared_ptr<Node>& DeterministicFiniteAutomaton::GetTraverser() {
  return traverser_;
}

void DeterministicFiniteAutomaton::MoveOnLetter(char transition) {
  traverser_ = traverser_->children[transition];
}

void DeterministicFiniteAutomaton::MoveOnSuffixLink() {
  traverser_ = traverser_->suffix_link;
}

void DeterministicFiniteAutomaton::BuildSuffixLinks() {
  root_->suffix_link = root_;
  root_->compressed_suffix_link = root_;

  std::queue<State> queue;
  for (auto& child : root_->children) {
    queue.push(State(child.second, child.first));
  }

  while (!queue.empty()) {
    std::shared_ptr<Node> current_node = queue.front().node;
    char current_ch = queue.front().ch;

    queue.pop();

    std::shared_ptr<Node> visitor = current_node->parent;
    while (true) {
      visitor = visitor->suffix_link;
      if (visitor->children.find(current_ch) != visitor->children.end() &&
          visitor->children[current_ch] != current_node) {
        current_node->suffix_link = visitor->children[current_ch];
        break;
      }

      if (visitor == root_) {
        current_node->suffix_link = root_;
        break;
      }
    }

    current_node->compressed_suffix_link = current_node->suffix_link->is_leaf ?
                                           current_node->suffix_link :
                                           current_node->suffix_link->compressed_suffix_link;

    for (auto& child : current_node->children) {
      queue.push(State(child.second, child.first));
    }
  }
}