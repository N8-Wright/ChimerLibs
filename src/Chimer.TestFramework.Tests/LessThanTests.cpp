#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(LessThanTests);

TEST(LessThanTests, Integers)
{
    AssertLessThan(1, 2);
}

TEST(LessThanTests, Longs)
{
    AssertLessThan(0L, 1L);
}

TEST(LessThanTests, Floats)
{
    AssertLessThan(0.1f, 2.1f);
}

TEST(LessThanTests, Doubles)
{
    AssertLessThan(9.01, 44.1);
}