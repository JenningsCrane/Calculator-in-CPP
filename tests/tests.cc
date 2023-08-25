#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../calcModel.h"

#define EPS 1e-4

jen::CalcModel parser;

TEST(Calc, Exp1) {
  const char* src = "4^acos(1.2/4)/tan(2*1.2)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = -6.31492;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp2) {
  const char* src = "2+2";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 4;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp3) {
  const char* src = "123+0.456";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 123.456;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp4) {
  const char* src = "log(-2)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = NAN;
  EXPECT_TRUE(std::isnan(res) && std::isnan(real_result));
}

TEST(Calc, Exp5) {
  const char* src = "-(-1)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 1;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp6) {
  const char* src = "cos(10 % 2.2)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 0.362358;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp7) {
  const char* src = "sqrt(ln(10))";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 1.517427;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp8) {
  const char* src = "atan(10)+sin(10)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 0.92710;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp9) {
  const char* src = "asin(1)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 1.570796;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp10) {
  const char* src = "10-20*(-10)";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 210;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp14) {
  const char* src = "2 ^ 3 ^ 2";
  double res = parser.ComputeLine(src, 0.0);
  double real_result = 512.0;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Graphic) {
  const char* src = "4^acos(x/4)/tan(2*x)";

  double x_numbers[3] = {-1.0, 0.0, 1.0};
  double y_numbers[3] = {0.0, 0.0, 0.0};

  parser.ComputeGraph(src, x_numbers, y_numbers, 3);

  EXPECT_TRUE(std::fabs(y_numbers[0] - 5.73301) <= EPS);
  EXPECT_TRUE(std::isinf(y_numbers[1]));
  EXPECT_TRUE(std::fabs(y_numbers[2] - -2.84528) <= EPS);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
