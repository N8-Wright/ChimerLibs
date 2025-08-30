#pragma once

#include "Chimer.Logging/Logger.hpp"

#include <vector>

namespace Chimer::TestFramework
{
	class TestSuite;
	class TestDriver
	{
		std::vector<std::reference_wrapper<TestSuite>> m_suites;
		std::shared_ptr<Logging::Logger> m_logger;

	public:
		explicit TestDriver(std::shared_ptr<Logging::Logger> logger);
		void AddTestSuite(TestSuite& suite);
		int Run(int argc, const char** argv);
	};

	TestDriver& GetDriver();
	int RunAllTests(int argc, const char** argv);
}
