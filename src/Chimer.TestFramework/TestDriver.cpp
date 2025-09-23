#include "Chimer.Logging/LoggerDelegate.hpp"
#include "Chimer.Logging/ConsoleLogger.hpp"

#include "Chimer/TestFramework/TestDriver.hpp"
#include "Chimer/TestFramework/TestSuite.hpp"
#include "Chimer/TestFramework/TestLogger.hpp"

#include "LogMessages.hpp"
#include <sstream>

using namespace Chimer::Logging;
namespace Chimer::TestFramework
{
    static auto logTestResults = MakeLoggerDelegate(
        LogLevel::Info,
        [](const TestCount testsPassed, const TestCount testsFailed) {
            std::stringstream os;
            os << "Total tests passed: " << testsPassed << ". "
               << "Total tests failed: " << testsFailed << ".";
            return os.str();
        });

    TestDriver::TestDriver(const gsl::not_null<Logging::Logger*> logger) :
        m_logger(logger)
    {
    }

    void TestDriver::AddTestSuite(const gsl::not_null<TestSuite*> suite)
    {
        m_suites.push_back(suite);
    }

    int TestDriver::Run(int, const char**)
    {
        std::vector<TestSuiteResult> results;
        TestCount passed;
        TestCount failed;
        for (auto& suite : m_suites)
        {
            const auto result = suite->Run();
            passed += result.Passed;
            failed += result.Failed;
        }

        logTestResults(m_logger, passed, failed);
        return static_cast<int>(failed.Count());
    }

    TestDriver& GetDriver()
    {
        static TestDriver testDriver(&GetLogger());
        return testDriver;
    }

    int RunAllTests(const int argc, const char** argv)
    {
        return GetDriver().Run(argc, argv);
    }
}
