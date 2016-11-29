//
// Created by whoami on 11/29/16.
//

#include <iostream>
#include <vector>

#include "PatternMatcher.h"

void PatternMatcher::CalculatePrefixFunction(const std::string &str, std::vector<int> *out_values) const {
  std::vector<int>& values = *out_values;
  values[0] = 0;

  for (int i = 1; i < str.size(); ++i) {
    // i + 1 - size of current prefix
    int predicted_suffix_value = values[i - 1];

    while (predicted_suffix_value > 0 && str[i] != str[predicted_suffix_value]) {
      predicted_suffix_value = values[predicted_suffix_value - 1];
    }

    if (str[i] == str[predicted_suffix_value]) {
      values[i] = predicted_suffix_value + 1;
    } else {
      values[i] = 0;
    }

  }
}

void PatternMatcher::DumpEntries() const {
  std::string auxiliary = pattern_ + kSeparator;

  std::vector<int> prefix_values(auxiliary.length());
  CalculatePrefixFunction(auxiliary, &prefix_values);

  int prefix_value = prefix_values.back();

  for (size_t i = 0; i < text_.length(); ++i) {
    // i + 1 - size of current prefix
    int predicted_suffix_value = prefix_value;

    while (predicted_suffix_value > 0 && text_[i] != pattern_[predicted_suffix_value]) {
      predicted_suffix_value = prefix_values[predicted_suffix_value - 1];
    }

    if (text_[i] == pattern_[predicted_suffix_value]) {
      prefix_value = predicted_suffix_value + 1;
    } else {
      prefix_value = 0;
    }

    if (prefix_value == pattern_.length()) {
      std::cout << static_cast<int>(i - pattern_.size() + 1) << " ";
    }
  }

  std::cout << std::endl;
}

std::vector<int> PatternMatcher::GetEntries() const {
  std::vector<int> result;

  std::string auxiliary = pattern_ + kSeparator;

  std::vector<int> prefix_values(auxiliary.length());
  CalculatePrefixFunction(auxiliary, &prefix_values);

  int prefix_value = prefix_values.back();

  for (size_t i = 0; i < text_.length(); ++i) {
    // i + 1 - size of current prefix
    int predicted_suffix_value = prefix_value;

    while (predicted_suffix_value > 0 && text_[i] != pattern_[predicted_suffix_value]) {
      predicted_suffix_value = prefix_values[predicted_suffix_value - 1];
    }

    if (text_[i] == pattern_[predicted_suffix_value]) {
      prefix_value = predicted_suffix_value + 1;
    } else {
      prefix_value = 0;
    }

    if (prefix_value == pattern_.length()) {
      result.push_back(static_cast<int>(i - pattern_.size() + 1));
    }
  }

  return result;
}

std::vector<int> PatternMatcher::GetEntriesNotOptimized() const {
  std::vector<int> result;

  std::string auxiliary = pattern_ + kSeparator + text_;

  std::vector<int> prefix_values(auxiliary.length());
  CalculatePrefixFunction(auxiliary, &prefix_values);

  for (size_t i = pattern_.length() + 1; i < auxiliary.length(); ++i) {
    if (prefix_values[i] == pattern_.length()) {
      result.push_back(static_cast<int>(i - 2 * pattern_.length()));
    }
  }

  return result;
}