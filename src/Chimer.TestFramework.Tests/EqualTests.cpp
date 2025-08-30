#include "Chimer.TestFramework/Test.hpp"

#include <compare>

TEST_SUITE_DEFINE(EqualTests);

TEST(EqualTests, Integers)
{
	ASSERT_EQ(100, 100);
}

TEST(EqualTests, Longs)
{
	ASSERT_EQ(1L, 1L);
}

TEST(EqualTests, Floats)
{
	ASSERT_EQ(77.7f, 77.7f);
}

TEST(EqualTests, Doubles)
{
	ASSERT_EQ(99.9, 99.9);
}

TEST(EqualTests, Strings)
{
	ASSERT_EQ(std::string("foo"), std::string("foo"));
}

TEST(EqualTests, StringViews)
{
	ASSERT_EQ(std::string_view("yard"), std::string_view("yard"));
}

TEST(EqualTests, CharPointers)
{
	const char* lhs = "bar";
	const char* rhs = "bar";

	ASSERT_EQ(lhs, rhs);
}

TEST(EqualTests, CharArrays)
{
	const char lhs[] = "baz";
	const char rhs[] = "baz";

	ASSERT_EQ(lhs, rhs);
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
	Foo lhs { 1, 9.1 };
	Foo rhs { 1, 9.1 };

	ASSERT_EQ(lhs, rhs);
}
