#include "TestSuite.hpp"
#include "Test.hpp"
#include "Chimer.Logging/LoggerDelegate.hpp"

#include <iostream>

using namespace Chimer::Logging;

auto logTestFailure = MakeLoggerDelegate(
	LogLevel::Error,
	[](std::string_view testClass, std::string_view testName, std::string_view reason)
	{
		std::stringstream os;
		os << "Failed test '" << testClass << "::" << testName << "' because " << reason;
		return os.str();
	}
);

auto logTestSuccess = MakeLoggerDelegate(
	LogLevel::Info,
	[](std::string_view testClass, std::string_view testName)
	{
		std::stringstream os;
		os << "Passed test '" << testClass << "::" << testName << "'";
		return os.str();
	}
);

auto logTestSuiteRunInfo = MakeLoggerDelegate(
	LogLevel::Info,
	[](std::string_view testSuite, int testsPassed, int testsFailed)
	{
		std::stringstream os;
		os << "Finished running all tests in " << testSuite << ". "
			<< "Tests Passed: " << testsPassed << ". "
			<< "Tests Failed: " << testsFailed << ".";
		return os.str();
	}
);

namespace Chimer::TestFramework
{
	TestSuite::TestSuite(std::string_view name, std::shared_ptr<Logging::Logger> logger)
		: m_name(name), m_logger(std::move(logger))
	{
	}

	void TestSuite::AddTest(std::unique_ptr<Test> test)
	{
		m_tests.push_back(std::move(test));
	}

	int TestSuite::Run(int, const char**)
	{
		int testsFailed = 0;
		int testsPassed = 0;
		for (auto& test : m_tests)
		{
			test->Run();
			if (test->Failed())
			{
				logTestFailure(m_logger, m_name, test->TestName(), test->Reason());
				testsFailed++;
			}
			else
			{
				logTestSuccess(m_logger, m_name, test->TestName());
				testsPassed++;
			}
		}

		logTestSuiteRunInfo(m_logger, m_name, testsPassed, testsFailed);
		return testsFailed;
	}
}