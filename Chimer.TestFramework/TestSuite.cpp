#include "TestSuite.hpp"
#include "Test.hpp"
#include "Chimer.Logging/LoggerDelegate.hpp"

#include <iostream>

using namespace Chimer::Logging;

static auto logTestFailure = MakeLoggerDelegate(
	LogLevel::Error,
	[](std::string_view testClass, std::string_view testName, std::string_view reason)
	{
		std::stringstream os;
		os << "Failed test '" << testClass << "::" << testName << "' because " << reason;
		return os.str();
	}
);

static auto logTestSuccess = MakeLoggerDelegate(
	LogLevel::Info,
	[](std::string_view testClass, std::string_view testName)
	{
		std::stringstream os;
		os << "Passed test '" << testClass << "::" << testName << "'";
		return os.str();
	}
);

static auto logTestSuiteRunInfo = MakeLoggerDelegate(
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
		static auto logTestRegister = MakeLoggerDelegate(
			LogLevel::Detail,
			[](std::string_view testClass, std::string_view testName)
			{
				std::stringstream os;
				os << "Registered " << testClass << "::" << testName;
				return os.str();
			}
		);

		logTestRegister(m_logger, m_name, test->TestName());
		m_tests.push_back(std::move(test));
	}

	TestSuiteResult TestSuite::Run(int, const char**)
	{
		TestSuiteResult suiteResult{};
		int testsFailed = 0;
		int testsPassed = 0;
		for (auto& test : m_tests)
		{
			test->Run();
			if (test->Failed())
			{
				auto result = test->GetFailureResult();
				logTestFailure(m_logger, m_name, result.TestName, result.Reason);
				suiteResult.TestsFailed++;
				suiteResult.FailedTests.push_back(std::move(result));
			}
			else
			{
				logTestSuccess(m_logger, m_name, test->TestName());
				suiteResult.TestsPassed++;
			}
		}

		logTestSuiteRunInfo(m_logger, m_name, testsPassed, testsFailed);
		return suiteResult;
	}
}