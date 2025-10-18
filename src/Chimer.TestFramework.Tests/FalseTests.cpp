#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(FalseTests);

TEST(FalseTests, Booleans)
{
    AssertFalse(false);
    AssertFalse(!true);
}

TEST(FalseTests, Weird)
{
    AssertFalse(!"str");
}

TEST(FalseTests, Expressions)
{
    AssertFalse(1 == 0);
    AssertFalse(std::string("abc") != std::string("abc"));
    AssertFalse(std::strcmp("9999", "123") == 0);
    AssertFalse([]() {
        if constexpr (1 + 1 != 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    });
}