#include "TestSuite.hpp"
#include "Test.hpp"
#include "Chimer.Logging/LoggerDelegate.hpp"

#include <iostream>

using namespace Chimer::Logging;

auto testFailure = MakeLoggerDelegate(
	LogLevel::Error,
	[](std::string_view testClass, std::string_view testName, std::string_view reason)
	{
		std::stringstream os;
		os << "Failed test '" << testClass << "::" << testName << "' because " << reason;
		return os.str();
	}
);

auto testSuccess = MakeLoggerDelegate(
	LogLevel::Info,
	[](std::string_view testClass, std::string_view testName)
	{
		std::stringstream os;
		os << "Passed test '" << testClass << "::" << testName << "'";
		return os.str();
	}
);

namespace Chimer::TestFramework
{
	TestSuite::TestSuite(std::shared_ptr<Logging::Logger> logger)
		: m_logger(std::move(logger))
	{
	}

	void TestSuite::AddTest(std::unique_ptr<Test> test)
	{
		m_tests.push_back(std::move(test));
	}

	int TestSuite::Run(int, const char**)
	{
		for (auto& test : m_tests)
		{
			test->Run();
			if (test->Failed())
			{
				testFailure(m_logger, test->TestClass(), test->TestName(), test->Reason());
			}
			else
			{
				testSuccess(m_logger, test->TestClass(), test->TestName());
			}
		}

		return 0;
	}
}