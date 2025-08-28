#include "Chimer.TestFramework/Test.hpp"

CHIMER_TEST_SUITE(EqualityTests);

CHIMER_TEST(EqualityTests, Integers)
{
	CHIMER_ASSERT_EQ(100, 100);
}

int main(int argc, const char** argv)
{
	return EqualityTests.Run(argc, argv);
}