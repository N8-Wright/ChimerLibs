#include "Chimer.TestFramework/Test.hpp"

TEST_SUITE_DEFINE(LessThanTests);

TEST(LessThanTests, Integers)
{
    ASSERT_LT(1, 2);
}

TEST(LessThanTests, Longs)
{
    ASSERT_LT(0L, 1L);
}

TEST(LessThanTests, Floats)
{
    ASSERT_LT(0.1f, 2.1f);
}

TEST(LessThanTests, Doubles)
{
    ASSERT_LT(9.01, 44.1);
}