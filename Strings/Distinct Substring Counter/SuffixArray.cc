//
// Created by whoami on 11/30/16.
//

#include <string>
#include <cmath>
#include <cassert>

#include "SuffixArray.h"

size_t LogBase2RoundedUp(size_t num) {
  return static_cast<size_t>(ceil(log2(num)));
}

SuffixArray::SuffixArray(const std::string &str)
    : is_valid_(false),
      str_(str) {

  equivalence_classes_.resize(LogBase2RoundedUp(str_.length()) + 1);
  for (int i = 0; i < equivalence_classes_.size(); ++i) {
    equivalence_classes_[i].resize(str_.length());
  }
}

void SuffixArray::ProcessInitialPhase(std::vector<int>* _order) {
  std::vector<int>& order = *_order;

  std::vector<int> count(kAlphabetSize, 0);
  for (auto& ch : str_) {
    count[ch] += 1;
  }

  for (int ch = 1; ch < kAlphabetSize; ++ch) {
    count[ch] += count[ch - 1];
  }

  for (int i = 0; i < order.size(); ++i) {
    order[count[str_[i]] - 1] = i;
    count[str_[i]] -= 1;
  }

  equivalence_classes_[0][order[0]] = 0;

  for (int i = 1; i < order.size(); ++i) {
    equivalence_classes_[0][order[i]] = equivalence_classes_[0][order[i - 1]];

    if (str_[order[i]] != str_[order[i - 1]]) {
      equivalence_classes_[0][order[i]] += 1;
    }
  }
}

void SuffixArray::BuildSuffixArray() {
  std::vector<int> order(str_.length());

  // Phase 0
  ProcessInitialPhase(&order);

  // Phase k
  for (int phase = 1; phase < equivalence_classes_.size(); ++phase) {
    std::vector<PendingMerge> pending;
    int shift = 1 << (phase - 1);

    for (int i = 0; i < str_.length(); ++i) {
      pending.push_back(PendingMerge(equivalence_classes_[phase - 1][i],
                                     equivalence_classes_[phase - 1][(i + shift) % str_.length()],
                                     i));
    }

    std::sort(pending.begin(), pending.end());

    for (int i = 0; i < order.size(); ++i) {
      order[i] = pending[i].start_pos;
    }

    equivalence_classes_[phase][order[0]] = 0;
    for (int i = 1; i < order.size(); ++i) {
      equivalence_classes_[phase][order[i]] = equivalence_classes_[phase][order[i - 1]];

      if (pending[i].left_class != pending[i - 1].left_class ||
          pending[i].right_class != pending[i - 1].right_class) {
        equivalence_classes_[phase][order[i]] += 1;
      }
    }
  }

  order_ = std::move(order);
  is_valid_ = true;
}

int SuffixArray::GetLongestCommonPrefixLength(int first_suffix_id, int second_suffix_id) const {
  assert(is_valid_);
  int result = 0;

  for (int phase = LogBase2RoundedUp(str_.length()); phase >= 0; --phase) {
    if (equivalence_classes_[phase][first_suffix_id] == equivalence_classes_[phase][second_suffix_id]) {
      result += (1 << phase);
      first_suffix_id += (1 << phase);
      second_suffix_id += (1 << phase);
    }
  }

  return result;
}

const std::vector<int>& SuffixArray::GetSuffixesOrder() const {
  return order_;
}