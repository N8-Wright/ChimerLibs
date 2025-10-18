#include "Chimer/TestFramework/Test.hpp"

TEST_SUITE_DEFINE(EqualTests);

TEST(EqualTests, Integers)
{
    AssertEqual(100, 100);
}

TEST(EqualTests, Longs)
{
    AssertEqual(1L, 1L);
}

TEST(EqualTests, Floats)
{
    AssertEqual(77.7f, 77.7f);
}

TEST(EqualTests, Doubles)
{
    AssertEqual(99.9, 99.9);
}

TEST(EqualTests, Strings)
{
    AssertEqual(std::string("foo"), std::string("foo"));
}

TEST(EqualTests, StringViews)
{
    AssertEqual(std::string_view("yard"), std::string_view("yard"));
}

TEST(EqualTests, CharPointers)
{
    const char* lhs = "bar";
    const char* rhs = "bar";

    AssertEqual(lhs, rhs);
}

TEST(EqualTests, CharArrays)
{
    constexpr char lhs[] = "baz";
    constexpr char rhs[] = "baz";

    AssertEqual(lhs, rhs);
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

TEST(EqualTests, Foo)
{
    constexpr Foo lhs{ 1, 9.1 };
    constexpr Foo rhs{ 1, 9.1 };

    AssertEqual(lhs, rhs);
}
