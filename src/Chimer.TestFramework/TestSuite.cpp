#include "Chimer.TestFramework/TestSuite.hpp"
#include "Chimer.TestFramework/Test.hpp"
#include "LogMessages.hpp"

#include "Chimer.Logging/LoggerDelegate.hpp"

#include <iostream>

using namespace Chimer::Logging;

namespace Chimer::TestFramework
{
    TestSuite::TestSuite(std::string_view name, gsl::not_null<std::shared_ptr<Logging::Logger>> logger) :
        m_name(name), m_logger(std::move(logger))
    {
    }

    void TestSuite::AddTest(std::unique_ptr<Test> test)
    {
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

        LogMessages::TestSuiteRunInfo(m_logger, m_name, suiteResult);
        return suiteResult;
    }
}
