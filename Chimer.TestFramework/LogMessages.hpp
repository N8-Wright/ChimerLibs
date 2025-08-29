#pragma once

#include "Chimer.Logging/LoggerDelegate.hpp"

#include <string>
#include <sstream>

namespace Chimer::TestFramework
{
	class LogMessages
	{
	public:
		static inline auto TestRegister = MakeLoggerDelegate2(
			Logging::LogLevel::Detail,
			[](std::string_view testClass, std::string_view testName) static
		{
			std::stringstream os;
			os << "Registered " << testClass << "::" << testName;
			return os.str();
		});

		static inline auto TestFailure = Logging::MakeLoggerDelegate2(
			Logging::LogLevel::Error,
			[](std::string_view testClass, std::string_view testName, std::string_view reason) static
		{
			std::stringstream os;
			os << "Failed test '" << testClass << "::" << testName << "' because " << reason;
			return os.str();
		});

		static inline auto TestSuccess = MakeLoggerDelegate2(
			Logging::LogLevel::Info,
			[](std::string_view testClass, std::string_view testName) static
		{
			std::stringstream os;
			os << "Passed test '" << testClass << "::" << testName << "'";
			return os.str();
		});

		static inline auto TestSuiteRunInfo = MakeLoggerDelegate2(
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