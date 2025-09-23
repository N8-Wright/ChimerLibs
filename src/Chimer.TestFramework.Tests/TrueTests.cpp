#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(TrueTests);

TEST(TrueTests, Booleans)
{
	ASSERT_TRUE(true);
	ASSERT_TRUE(!false);
}

TEST(TrueTests, Weird)
{
	ASSERT_TRUE("str");
}