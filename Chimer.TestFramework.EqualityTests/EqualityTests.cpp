#include "Chimer.TestFramework/Test.hpp"

TEST_SUITE(EqualityTests);

TEST(EqualityTests, Integers)
{
	ASSERT_EQ(100, 100);
}

TEST(EqualityTests, Longs)
{
	ASSERT_EQ(1L, 1L);
}

TEST(EqualityTests, Floats)
{
	ASSERT_EQ(77.7f, 77.7f);
}

TEST(EqualityTests, Doubles)
{
	ASSERT_EQ(99.9, 99.9);
}

TEST(EqualityTests, Strings)
{
	ASSERT_EQ(std::string("foo"), std::string("foo"));
}

TEST(EqualityTests, StringViews)
{
	ASSERT_EQ(std::string_view("yard"), std::string_view("yard"));
}

TEST(EqualityTests, CharPointers)
{
	const char* lhs = "bar";
	const char* rhs = "bar";

	ASSERT_EQ(lhs, rhs);
}

TEST(EqualityTests, CharArrays)
{
	const char lhs[] = "baz";
	const char rhs[] = "baz";

	ASSERT_EQ(lhs, rhs);
}

int main(int argc, const char** argv)
{
	return EqualityTests.Run(argc, argv);
}