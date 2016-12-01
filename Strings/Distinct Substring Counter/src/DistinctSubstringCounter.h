//
// Created by whoami on 11/30/16.
//

#ifndef DISTINCT_SUBSTRING_COUNTER_DISTINCTSUBSTRINGCOUNTER_H
#define DISTINCT_SUBSTRING_COUNTER_DISTINCTSUBSTRINGCOUNTER_H

#include "SuffixArray.h"

// Wrap over Suffix Array class
// Find number of distinct substrings
class DistinctSubstringCounter {
 public:
  explicit DistinctSubstringCounter(const std::string& str);
  int64_t GetNumberOfDistinctSubstrings() const;

 private:

  const char kSeparator = '$';

  std::string str_;
  SuffixArray suffix_array_;
};


#endif //DISTINCT_SUBSTRING_COUNTER_DISTINCTSUBSTRINGCOUNTER_H
