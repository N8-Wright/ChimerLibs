#include "Chimer.TestFramework/Test.hpp"

TEST_SUITE_DEFINE(FalseTests);

TEST(FalseTests, Booleans)
{
    ASSERT_FALSE(false);
    ASSERT_FALSE(!true);
}

TEST(FalseTests, Weird)
{
    ASSERT_FALSE(!"str");
}