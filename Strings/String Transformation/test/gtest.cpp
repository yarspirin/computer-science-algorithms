//
// Created by whoami on 11/30/16.
//

#include "../src/Transformer.h"

#include "gtest/gtest.h"

TEST(BasicTest, PrefixFuncRecover) {
  std::vector<int> values = {0, 1, 2, 3, 0};
  Transformer transformer;
  ASSERT_EQ(transformer.TransformByPrefixValues(values), "aaaab");
}

TEST(BasicTest, ZFuncRecover) {
  std::vector<int> values = {5, 3, 2, 1, 0};
  Transformer transformer;
  ASSERT_EQ(transformer.TransformByZValues(values), "aaaab");
}

TEST(BasicTest, ZFuncToPrefixFunc) {
  std::vector<int> z_values = {5, 3, 2, 1, 0};
  std::vector<int> prefix_values = {0, 1, 2, 3, 0};

  Transformer transformer;

  std::vector<int> converted = transformer.TransformFromZValuesToPrefixValues(z_values);
  ASSERT_EQ(converted.size(), prefix_values.size());

  for (int i = 0; i < converted.size(); ++i) {
    ASSERT_EQ(converted[i], prefix_values[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}