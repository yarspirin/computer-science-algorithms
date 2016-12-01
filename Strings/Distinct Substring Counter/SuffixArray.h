//
// Created by whoami on 11/30/16.
//

#ifndef DISTINCT_SUBSTRING_COUNTER_SUFFIXARRAY_H
#define DISTINCT_SUBSTRING_COUNTER_SUFFIXARRAY_H

#include <string>
#include <vector>

size_t LogBase2RoundedUp(size_t num);

// Helper struct
// Store equivalent classes of merged substings and the start position
struct PendingMerge {
  PendingMerge(int _left_class, int _right_class, int _start_pos)
      : left_class(_left_class),
        right_class(_right_class),
        start_pos(_start_pos) { }

  bool operator < (const PendingMerge& other) const {
    return left_class < other.left_class || ((left_class == other.left_class && right_class < other.right_class) ||
        (left_class == other.left_class && right_class == other.right_class && start_pos < other.start_pos));
  }

  int left_class;
  int right_class;
  int start_pos;
};

// Efficient data structure
// Keep all suffixes of a given string sorted
// Provide quick algorithm to find longest common prefix of two given suffixes
class SuffixArray {
 public:
  explicit SuffixArray(const std::string& str);
  void BuildSuffixArray();
  int GetLongestCommonPrefixLength(int first_suffix_id, int second_suffix_id) const;
  const std::vector<int>& GetSuffixesOrder() const;

 private:

  void ProcessInitialPhase(std::vector<int>* order);

  const int kAlphabetSize = 256;
  bool is_valid_;

  std::vector<int> order_;
  std::vector<std::vector<int> > equivalence_classes_;
  std::string str_;
};


#endif //DISTINCT_SUBSTRING_COUNTER_SUFFIXARRAY_H
