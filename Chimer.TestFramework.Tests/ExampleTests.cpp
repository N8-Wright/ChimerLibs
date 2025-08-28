#include "Chimer.TestFramework/Test.hpp"

#include <iostream>

TEST_SUITE(ExampleTests);
TEST(ExampleTests, SimpleChecks)
{
	ASSERT_EQ(1, 2);
	ASSERT_EQ(2, 2);
}

int main(int argc, const char** argv)
{
	ExampleTests.Run(argc, argv);
}