#include "Chimer.TestFramework/Test.hpp"

#include <iostream>

CHIMER_TEST_SUITE(ExampleTests);
CHIMER_TEST(ExampleTests, SimpleChecks)
{
	CHIMER_ASSERT_EQ(1, 2);
	CHIMER_ASSERT_EQ(2, 2);
}

int main(int argc, const char** argv)
{
	ExampleTests.Run(argc, argv);
}