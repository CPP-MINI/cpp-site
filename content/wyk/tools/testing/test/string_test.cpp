#include <gtest/gtest.h>

#include "functions.hpp"

using namespace functions;

class StringTest : public ::testing::Test {
protected:
  string str;
  string other;

  void SetUp() { str = "Hello World!"; }
};

TEST_F(StringTest, ConstructorWorks) {
  EXPECT_STREQ(str.data(), "Hello World!");
}

TEST_F(StringTest, EmptyByDefault) {
  EXPECT_STREQ(other.data(), "");
}

TEST_F(StringTest, SizeWorks) {
  EXPECT_EQ(str.size(), 12);
}

TEST_F(StringTest, CanCopy) {
  other = str;
  EXPECT_STREQ(other.data(), "Hello World!");
  EXPECT_STREQ(str.data(), "Hello World!");
}

TEST_F(StringTest, CanMove) {
  other = std::move(str);
  EXPECT_STREQ(other.data(), "Hello World!");
}
