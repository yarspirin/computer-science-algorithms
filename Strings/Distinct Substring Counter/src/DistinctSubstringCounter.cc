//
// Created by whoami on 11/30/16.
//

#include "DistinctSubstringCounter.h"

DistinctSubstringCounter::DistinctSubstringCounter(const std::string& str)
    : str_(str + kSeparator),
      suffix_array_(SuffixArray(str + kSeparator)) {
  suffix_array_.BuildSuffixArray();
}

int64_t DistinctSubstringCounter::GetNumberOfDistinctSubstrings() const {
  int64_t result = static_cast<int64_t>(str_.length() * (str_.length() - 1) / 2);

  const std::vector<int>& order = suffix_array_.GetSuffixesOrder();

  for (int i = 0; i < str_.length() - 1; ++i) {
    result -= suffix_array_.GetLongestCommonPrefixLength(order[i], order[i + 1]);
  }

  return result;
}