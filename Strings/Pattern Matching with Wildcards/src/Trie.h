//
// Created by whoami on 12/1/16.
//

#ifndef PATTERN_MATCHING_WITH_QUESTION_MARKS_TRIE_H
#define PATTERN_MATCHING_WITH_QUESTION_MARKS_TRIE_H

#include <memory>
#include <unordered_map>
#include <vector>

// Trie node
struct Node {

  Node()
      : is_leaf(false),
        parent(nullptr),
        suffix_link(nullptr),
        compressed_suffix_link(nullptr) { }

  Node(std::shared_ptr<Node>& _parent)
      : is_leaf(false),
        parent(_parent),
        suffix_link(nullptr),
        compressed_suffix_link(nullptr) { }

  bool is_leaf;
  std::vector<int> ids;

  std::shared_ptr<Node> parent;
  std::shared_ptr<Node> suffix_link;
  std::shared_ptr<Node> compressed_suffix_link;

  std::unordered_map<char, std::shared_ptr<Node>> children;
};

// Storage of strings
// Provide efficient Put() and Contains() methods
class Trie {
 public:
  Trie() : root_(std::make_shared<Node>(Node())) { }
  void Put(const std::string& sample, int id);
  bool Contains(const std::string& sample);

 protected:
  std::shared_ptr<Node> root_;

 private:
  void PutAtNode(const std::string& sample, int pos, std::shared_ptr<Node>& node, int id);
  bool ContainsAtNode(const std::string& sample, int pos, std::shared_ptr<Node>& node);
};


#endif //PATTERN_MATCHING_WITH_QUESTION_MARKS_TRIE_H
