//
// Created by whoami on 11/24/16.
//

#include "gtest/gtest.h"

#include "../src/Solver.h"

TEST(BasicTest, SampleTest) {
  std::string origin = "00?";
  std::string pattern = "1?";

  Solver solver(origin, pattern);
  solver.Init();

  ASSERT_EQ(solver.FindMaxCorrelation(), 2);

  std::pair<std::string, std::string> ans = solver.RetrieveTemplates();

  ASSERT_EQ(ans.first, "000");
  ASSERT_EQ(ans.second, "10");
}

TEST(BasicTest, YetAnotherTest) {
  std::string origin = "?1?";
  std::string pattern = "0?";

  Solver solver(origin, pattern);
  solver.Init();

  ASSERT_EQ(solver.FindMaxCorrelation(), 1);

  std::pair<std::string, std::string> ans = solver.RetrieveTemplates();

  ASSERT_EQ(ans.first, "011");
  ASSERT_EQ(ans.second, "01");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}