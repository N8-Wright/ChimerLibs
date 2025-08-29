#include "Chimer.Logging/LoggerDelegate.hpp"
#include "Chimer.Logging/ConsoleLogger.hpp"

#include "TestDriver.hpp"
#include "TestSuite.hpp"
#include <sstream>

using namespace Chimer::Logging;

static auto logTestResults = MakeLoggerDelegate2(
	LogLevel::Info,
	[](size_t testsPassed, size_t testsFailed)
	{
		std::stringstream os;
		os << "Total tests passed: " << testsPassed << ". "
			<< "Total tests failed: " << testsFailed << ".";
		return os.str();
	}
);

namespace Chimer::TestFramework
{
	TestDriver::TestDriver(std::shared_ptr<Logging::Logger> logger)
		: m_logger(std::move(logger))
	{
	}

	void TestDriver::AddTestSuite(TestSuite& suite)
	{
		m_suites.push_back(suite);
	}

	int TestDriver::Run(int, const char**)
	{
		std::vector<TestSuiteResult> results;
		size_t testsPassed = 0;
		size_t testsFailed = 0;
		for (auto& suite : m_suites)
		{
			const auto result = suite.get().Run();
			testsPassed += result.TestsPassed;
			testsFailed += result.TestsFailed;
		}

		logTestResults(m_logger, testsPassed, testsFailed);
		return static_cast<int>(testsFailed);
	}

	TestDriver& GetDriver()
	{
		static TestDriver testDriver(std::make_shared<ConsoleLogger>(LogLevel::Info));
		return testDriver;
	}

	int RunAllTests(int argc, const char** argv)
	{
		return GetDriver().Run(argc, argv);
	}
}