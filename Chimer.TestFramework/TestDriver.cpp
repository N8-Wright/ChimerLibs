#include "TestDriver.hpp"
#include "TestSuite.hpp"
#include <iostream>

namespace Chimer::TestFramework
{
	void TestDriver::AddTestSuite(TestSuite& suite)
	{
		m_suites.push_back(suite);
	}

	int TestDriver::Run(int argc, const char** argv)
	{
		int result = 0;
		for (auto& suite : m_suites)
		{
			result += suite.get().Run(argc, argv);
		}

		return result;
	}

	TestDriver& GetDriver()
	{
		static TestDriver testDriver;
		return testDriver;
	}

	int RunAllTests(int argc, const char** argv)
	{
		return GetDriver().Run(argc, argv);
	}
}