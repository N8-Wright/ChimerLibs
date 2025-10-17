#include "Chimer/TestFramework/TestSuite.hpp"
#include "Chimer/TestFramework/Test.hpp"
#include "Chimer/TestFramework/TestException.hpp"

#include "LogMessages.hpp"

#include "Chimer/Logging/LoggerDelegate.hpp"

#include <iostream>

using namespace Chimer::Logging;

namespace Chimer::TestFramework
{
    TestSuite::TestSuite(const std::string_view name, const gsl::not_null<Logging::Logger*> logger) :
        m_name(name), m_logger(logger)
    {
    }

    void TestSuite::AddTest(std::unique_ptr<Test> test)
    {
        if (test == nullptr)
        {
            throw std::runtime_error("Test cannot be null");
        }

        static auto TestRegister = MakeLoggerDelegate(
            Logging::LogLevel::Detail,
            [](std::string_view testClass, std::string_view testName) static {
                std::stringstream os;
                os << "Registered " << testClass << "::" << testName;
                return os.str();
            });

        TestRegister(m_logger, m_name, test->TestName());
        m_tests.push_back(std::move(test));
    }

    TestSuiteResult TestSuite::Run()
    {
        TestSuiteResult suiteResult{};
        for (auto& test : m_tests)
        {
            try
            {
                test->Run();
                if (test->Failed())
                {
                    auto result = test->GetFailureResult();
                    LogMessages::TestFailure(m_logger, m_name, result);
                    ++suiteResult.Failed;
                    suiteResult.FailedTests.push_back(std::move(result));
                }
                else
                {
                    LogMessages::TestSuccess(m_logger, m_name, test->TestName());
                    ++suiteResult.Passed;
                }
            }
            catch (const TestException& e)
            {
                auto reason = std::string(e.what());
                test->MarkFailed(std::move(reason), e.SourceLocation());
            }
            catch (const std::exception& e)
            {
                auto reason = std::string(e.what());
                test->MarkFailed(std::move(reason), std::source_location::current());
            }
        }

        LogMessages::TestSuiteRunInfo(m_logger, m_name, suiteResult);
        return suiteResult;
    }
}
