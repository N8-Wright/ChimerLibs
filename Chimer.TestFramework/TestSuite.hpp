#pragma once
#include <vector>
#include <memory>
namespace Chimer::TestFramework
{
	class Test;
	class TestSuite
	{
		std::vector<std::unique_ptr<Test>> m_tests;
	public:
		void AddTest(std::unique_ptr<Test> test);
		int Run(int argc, const char** argv);
	};
}

#define CHIMER_TEST_SUITE(suite) \
	static Chimer::TestFramework::TestSuite suite;