#include <gtest/gtest.h>

#include "functions.hpp"

using namespace functions;

TEST(FibTest, Fib0) {
  EXPECT_EQ(fib(0), 0);
}

TEST(FibTest, Fib1) {
  EXPECT_EQ(fib(1), 1);
}

TEST(FibTest, Fib2) {
  EXPECT_EQ(fib(2), 1);
}

