//
// Created by whoami on 12/1/16.
//

#include "gtest/gtest.h"

#include "../src/DistinctSubstringCounter.h"

TEST(BasicTest, SampleTest) {
  DistinctSubstringCounter distinct_substring_counter("aaba");
  ASSERT_EQ(distinct_substring_counter.GetNumberOfDistinctSubstrings(), 8);
}

TEST(BasicTest, WeirdTest) {
  DistinctSubstringCounter distinct_substring_counter("aaaa");
  ASSERT_EQ(distinct_substring_counter.GetNumberOfDistinctSubstrings(), 4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}