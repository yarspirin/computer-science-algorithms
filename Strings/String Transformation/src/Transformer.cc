//
// Created by whoami on 11/30/16.
//

#include "Transformer.h"

std::string Transformer::TransformByPrefixValues(const std::vector<int> &values) {
  std::string result = "a";

  for (int i = 1; i < values.size(); ++i) {
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      int predicted_suffix_value = values[i - 1];

      while (predicted_suffix_value > 0 && ch != result[predicted_suffix_value]) {
        predicted_suffix_value = values[predicted_suffix_value - 1];
      }

      if ((ch == result[predicted_suffix_value] && values[i] == predicted_suffix_value + 1) ||
          (ch != result[predicted_suffix_value] && values[i] == predicted_suffix_value)) {
        result += ch;
        break;
      }
    }
  }

  return result;
}

std::vector<int> Transformer::TransformFromZValuesToPrefixValues(const std::vector<int> &values) {
  std::vector<int> result(values.size());

  for (int i = 1; i < values.size(); ++i) {
    for (int j = values[i] - 1; j >= 0; --j) {
      if (result[i + j] > 0) {
        break;
      }

      result[i + j] = j + 1;
    }
  }

  return result;
}

std::string Transformer::TransformByZValues(const std::vector<int> &values) {
  std::vector<int> prefix_values = TransformFromZValuesToPrefixValues(values);
  return TransformByPrefixValues(prefix_values);
}