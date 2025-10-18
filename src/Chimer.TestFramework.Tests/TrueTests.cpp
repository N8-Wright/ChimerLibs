#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(TrueTests);

TEST(TrueTests, Booleans)
{
    AssertTrue(true);
    AssertTrue(!false);
}

TEST(TrueTests, Weird)
{
    AssertTrue("str");
}

TEST(TrueTests, Expressions)
{
    AssertTrue(1 != 0);
    AssertTrue(std::string("abc") == std::string("abc"));
    AssertTrue(std::strcmp("9999", "123") != 0);
    AssertTrue([]() {
        if constexpr (1 + 1 == 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    });
}