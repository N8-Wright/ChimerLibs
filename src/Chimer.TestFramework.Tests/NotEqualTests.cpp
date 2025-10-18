#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(NotEqualTests);

TEST(NotEqualTests, Integers)
{
    AssertNotEqual(99, 88);
}

TEST(NotEqualTests, Longs)
{
    AssertNotEqual(7134L, 9123L);
}

TEST(NotEqualTests, Floats)
{
    AssertNotEqual(88.09f, 44.04f);
}

TEST(NotEqualTests, Doubles)
{
    AssertNotEqual(88.09, 44.04);
}

TEST(NotEqualTests, Strings)
{
    AssertNotEqual(std::string("foo"), std::string("bar"));
}

TEST(NotEqualTests, StringViews)
{
    AssertNotEqual(std::string_view("yard"), std::string_view("yards"));
}

TEST(NotEqualTests, CharPointers)
{
    const auto lhs = "bar";
    const auto rhs = "baz";

    AssertNotEqual(lhs, rhs);
}

TEST(NotEqualTests, CharArrays)
{
    constexpr char lhs[] = "baz";
    constexpr char rhs[] = "bar";

    AssertNotEqual(lhs, rhs);
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
    constexpr Foo lhs{ 1, 9.111 };
    constexpr Foo rhs{ 1, 9.1 };

    AssertNotEqual(lhs, rhs);
}