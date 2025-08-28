#pragma once

#include <vector>

namespace Chimer::TestFramework
{
	class TestSuite;
	class TestDriver
	{
		std::vector<std::reference_wrapper<TestSuite>> m_suites;

	public:
		void AddTestSuite(TestSuite& suite);
		int Run(int argc, const char** argv);
	};

	TestDriver& GetDriver();
	int RunAllTests(int argc, const char** argv);
}
