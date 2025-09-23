#pragma once
#include "Chimer/TestFramework/TestFailureResult.hpp"
#include "Chimer/TestFramework/TestSuiteResult.hpp"

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
            [](const std::string_view testClass, const TestFailureResult& failure) static {
                std::stringstream os;
                os << "Failed test '" << testClass << "::" << failure.TestName << "' because " << failure.Reason << ": "
                   << failure.Location.file_name() << '('
                   << failure.Location.line() << ':'
                   << failure.Location.column() << ")";

                return os.str();
            });

        static inline auto TestSuccess = MakeLoggerDelegate(
            Logging::LogLevel::Info,
            [](const std::string_view testClass, const std::string_view testName) static {
                std::stringstream os;
                os << "Passed test '" << testClass << "::" << testName << "'";
                return os.str();
            });

        static inline auto TestSuiteRunInfo = MakeLoggerDelegate(
            Logging::LogLevel::Info,
            [](const std::string_view suite, const TestSuiteResult& result) static {
                std::stringstream os;
                os << "Finished running all tests in " << suite << ". "
                   << "Tests Passed: " << result.Passed << ". "
                   << "Tests Failed: " << result.Failed << ".";
                return os.str();
            });
    };
}