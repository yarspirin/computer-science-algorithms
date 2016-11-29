//
// Created by whoami on 11/29/16.
//

#ifndef MYPROJECTNAME_PATTERNMATCHER_H
#define MYPROJECTNAME_PATTERNMATCHER_H


// Calculate all entries of given pattern in given text
// Based on Knuth-Morris-Pratt algorithm
class PatternMatcher {
 public:

  PatternMatcher(const std::string& pattern, const std::string& text)
      : pattern_(pattern),
        text_(text) { }

  // Write entries of the pattern in the text to the stdout
  // Require only O(|pattern|) extra memory
  void DumpEntries() const;

  // Return vector of entries of the pattern in the text
  // Require O(|pattern| + |result|) extra memory, but allow using entries
  std::vector<int> GetEntries() const;

  // Return vector of entries of the pattern in the text
  // Require O(|pattern| + |text| + |result|) extra memory, but allow using entries (more clear implementation)
  std::vector<int> GetEntriesNotOptimized() const;

 private:

  // Separate pattern and text strings
  const char kSeparator = '#';

  void CalculatePrefixFunction(const std::string& str, std::vector<int>* values) const;

  std::string pattern_;
  std::string text_;
};


#endif //MYPROJECTNAME_PATTERNMATCHER_H
