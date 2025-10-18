#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(GreaterThanTests);

TEST(GreaterThanTests, Integers)
{
    AssertGreaterThan(101, 88);
}

TEST(GreaterThanTests, Longs)
{
    AssertGreaterThan(999L, 0L);
}

TEST(GreaterThanTests, Floats)
{
    AssertGreaterThan(77.7f, 77.0f);
}

TEST(GreaterThanTests, Doubles)
{
    AssertGreaterThan(99.9, 1.1);
}