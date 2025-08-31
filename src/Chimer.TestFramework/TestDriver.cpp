#include "Chimer.Logging/LoggerDelegate.hpp"
#include "Chimer.Logging/ConsoleLogger.hpp"

#include "Chimer.TestFramework/TestDriver.hpp"
#include "Chimer.TestFramework/TestSuite.hpp"

#include "LogMessages.hpp"
#include <sstream>

using namespace Chimer::Logging;
namespace Chimer::TestFramework
{
    static auto logTestResults = MakeLoggerDelegate(
        LogLevel::Info,
        [](TestCount testsPassed, TestCount testsFailed) {
            std::stringstream os;
            os << "Total tests passed: " << testsPassed << ". "
               << "Total tests failed: " << testsFailed << ".";
            return os.str();
        });

    TestDriver::TestDriver(gsl::not_null<std::shared_ptr<Logging::Logger>> logger) :
        m_logger(std::move(logger))
    {
    }

    void TestDriver::AddTestSuite(gsl::not_null<TestSuite*> suite)
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
        static TestDriver testDriver(std::make_shared<ConsoleLogger>(LogLevel::Info));
        return testDriver;
    }

    int RunAllTests(int argc, const char** argv)
    {
        return GetDriver().Run(argc, argv);
    }
}
