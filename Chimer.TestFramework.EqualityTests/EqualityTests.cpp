#include "Chimer.TestFramework/Test.hpp"

CHIMER_TEST_SUITE(EqualityTests);

CHIMER_TEST(EqualityTests, Integers)
{
	CHIMER_ASSERT_EQ(100, 100);
}

CHIMER_TEST(EqualityTests, Longs)
{
	CHIMER_ASSERT_EQ(1L, 1L);
}

int main(int argc, const char** argv)
{
	return EqualityTests.Run(argc, argv);
}