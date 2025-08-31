#include "Chimer.TestFramework/Test.hpp"

TEST_SUITE_DEFINE(NotEqualTests);

TEST(NotEqualTests, Integers)
{
    ASSERT_NOT_EQ(99, 88);
}

TEST(NotEqualTests, Longs)
{
    ASSERT_NOT_EQ(7134L, 9123L);
}

TEST(NotEqualTests, Floats)
{
    ASSERT_NOT_EQ(88.09f, 44.04f);
}

TEST(NotEqualTests, Doubles)
{
    ASSERT_NOT_EQ(88.09, 44.04);
}

TEST(NotEqualTests, Strings)
{
    ASSERT_NOT_EQ(std::string("foo"), std::string("bar"));
}

TEST(NotEqualTests, StringViews)
{
    ASSERT_NOT_EQ(std::string_view("yard"), std::string_view("yards"));
}

TEST(NotEqualTests, CharPointers)
{
    const char* lhs = "bar";
    const char* rhs = "baz";

    ASSERT_NOT_EQ(lhs, rhs);
}

TEST(NotEqualTests, CharArrays)
{
    constexpr char lhs[] = "baz";
    constexpr char rhs[] = "bar";

    ASSERT_NOT_EQ(lhs, rhs);
}

class Foo
{
public:
    int x;
    double y;
    auto operator<=>(const Foo&) const = default;
    friend std::ostream& operator<<(std::ostream& os, const Foo& foo)
    {
        return os << "[" << foo.x << ", " << foo.y << "]";
    }
};

TEST(NotEqualTests, Foo)
{
    Foo lhs{ 1, 9.111 };
    Foo rhs{ 1, 9.1 };

    ASSERT_NOT_EQ(lhs, rhs);
}