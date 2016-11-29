//
// Created by whoami on 11/29/16.
//

#include "gtest/gtest.h"

#include "../src/PatternMatcher.h"

TEST(BasicTest, SampleTest) {
  PatternMatcher pattern_matcher("aba", "abacababa");

  std::vector<int> entries = pattern_matcher.GetEntries();
  std::vector<int> ans = {0, 4, 6};

  ASSERT_EQ(entries.size(), ans.size());
  for (int i = 0; i < entries.size(); ++i) {
    ASSERT_EQ(entries[i], ans[i]);
  }
}

TEST(BasicTest, WeirdTest) {
  PatternMatcher pattern_matcher("a", "aaaaaaa");

  std::vector<int> entries = pattern_matcher.GetEntries();
  std::vector<int> ans = {0, 1, 2, 3, 4, 5, 6};

  ASSERT_EQ(entries.size(), ans.size());
  for (int i = 0; i < entries.size(); ++i) {
    ASSERT_EQ(entries[i], ans[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}