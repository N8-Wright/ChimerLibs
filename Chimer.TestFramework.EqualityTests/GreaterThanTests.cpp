#include "Chimer.TestFramework/Test.hpp"

TEST_SUITE_DEFINE(GreaterThanTests);

TEST(GreaterThanTests, Integers)
{
	ASSERT_GT(101, 88);
}

TEST(GreaterThanTests, Longs)
{
	ASSERT_GT(999L, 0L);
}

TEST(GreaterThanTests, Floats)
{
	ASSERT_GT(77.7f, 77.0f);
}

TEST(GreaterThanTests, Doubles)
{
	ASSERT_GT(99.9, 1.1);
}