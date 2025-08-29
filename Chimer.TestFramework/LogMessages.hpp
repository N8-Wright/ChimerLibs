#pragma once
#include "Chimer.TestFramework/TestFailureResult.hpp"

#include "Chimer.Logging/LoggerDelegate.hpp"

#include <string>
#include <sstream>

namespace Chimer::TestFramework
{
	class LogMessages
	{
	public:
		static inline auto TestFailure = Logging::MakeLoggerDelegate(
			Logging::LogLevel::Error,
			[](std::string_view testClass, const TestFailureResult& failure) static
		{
			std::stringstream os;
			os << "Failed test '" << testClass << "::" << failure.TestName << "' because " << failure.Reason << ": "
				<< failure.Location.file_name() << '('
				<< failure.Location.line() << ':'
				<< failure.Location.column() << ")";

			return os.str();
		});

		static inline auto TestSuccess = MakeLoggerDelegate(
			Logging::LogLevel::Info,
			[](std::string_view testClass, std::string_view testName) static
		{
			std::stringstream os;
			os << "Passed test '" << testClass << "::" << testName << "'";
			return os.str();
		});

		static inline auto TestSuiteRunInfo = MakeLoggerDelegate(
			Logging::LogLevel::Info,
			[](std::string_view testSuite, int testsPassed, int testsFailed) static
		{
			std::stringstream os;
			os << "Finished running all tests in " << testSuite << ". "
				<< "Tests Passed: " << testsPassed << ". "
				<< "Tests Failed: " << testsFailed << ".";
			return os.str();
		});
	};
}