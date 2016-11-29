//
// Created by whoami on 11/30/16.
//

#ifndef PROJECT_TRANSFORMER_H
#define PROJECT_TRANSFORMER_H

#include <string>
#include <vector>

// Build the original string by its prefix/z - function representation
class Transformer {
 public:

  static std::string TransformByPrefixValues(const std::vector<int>& values);

  static std::string TransformByZValues(const std::vector<int>& values);

  static std::vector<int> TransformFromZValuesToPrefixValues(const std::vector<int>& values);
};


#endif //PROJECT_TRANSFORMER_H
