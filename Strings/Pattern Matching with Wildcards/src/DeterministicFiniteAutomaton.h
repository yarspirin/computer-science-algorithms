//
// Created by whoami on 12/1/16.
//

#ifndef PATTERN_MATCHING_WITH_QUESTION_MARKS_DETERMINISTICFINITEAUTOMATON_H
#define PATTERN_MATCHING_WITH_QUESTION_MARKS_DETERMINISTICFINITEAUTOMATON_H

#include "Trie.h"

// Queue state
struct State {
  State (std::shared_ptr<Node>& _node, char _ch)
      : node(_node), ch(_ch) { }

  std::shared_ptr<Node> node;
  char ch;
};

// Help to implement Aho-Corasick algorithm
class DeterministicFiniteAutomaton : public Trie {
 public:
  DeterministicFiniteAutomaton()
      : traverser_(root_) { }

  std::shared_ptr<Node>& GetTraverser();
  std::shared_ptr<Node>& GetRoot();
  void MoveOnLetter(char transition);
  void MoveOnSuffixLink();

  // Compress all transitions in BFS traverse
  void BuildSuffixLinks();

 private:
  std::shared_ptr<Node> traverser_;
};


#endif //PATTERN_MATCHING_WITH_QUESTION_MARKS_DETERMINISTICFINITEAUTOMATON_H
