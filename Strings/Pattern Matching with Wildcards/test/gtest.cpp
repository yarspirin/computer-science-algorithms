//
// Created by whoami on 12/6/16.
//

#include <vector>
#include <string>

#include "../src/Solver.h"
#include "gtest/gtest.h"

TEST(BasicTest, SampleTest) {
  Solver solver("ab??aba", "ababacaba");

  std::vector<int> answer = {2};
  std::vector<int> solver_answer = solver.GetEntries();

  ASSERT_EQ(solver_answer.size(), answer.size());

  for (int i = 0; i < solver_answer.size(); ++i) {
    ASSERT_EQ(solver_answer[i], answer[i]);
  }
}

TEST(BasicTest, TrickyTest) {
  Solver solver("????", "asdasdsa");

  std::vector<int> answer = {0, 1, 2, 3, 4};
  std::vector<int> solver_answer = solver.GetEntries();

  ASSERT_EQ(solver_answer.size(), answer.size());

  for (int i = 0; i < solver_answer.size(); ++i) {
    ASSERT_EQ(solver_answer[i], answer[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}