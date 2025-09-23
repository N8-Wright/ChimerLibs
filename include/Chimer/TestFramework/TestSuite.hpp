#pragma once
#include "Chimer/TestFramework/TestSuiteResult.hpp"
#include "Chimer/TestFramework/TestLogger.hpp"

#include "Chimer/Logging/Logger.hpp"
#include "Chimer/Logging/ConsoleLogger.hpp"

#include <vector>
#include <memory>
#include <string_view>

#include <gsl/gsl>

namespace Chimer::TestFramework
{
    class Test;
    class TestSuite
    {
        std::string m_name;
        std::vector<std::unique_ptr<Test>> m_tests;
        gsl::not_null<Logging::Logger*> m_logger;

    public:
        TestSuite(std::string_view name, gsl::not_null<Logging::Logger*> logger);
        void AddTest(std::unique_ptr<Test> test);
        TestSuiteResult Run();
    };
}

#define TEST_SUITE_DECLARE(suite) \
    extern Chimer::TestFramework::TestSuite suite;

#define TEST_SUITE_DEFINE(suite)                                                         \
    Chimer::TestFramework::TestSuite suite(#suite, &Chimer::TestFramework::GetLogger()); \
    class suite##_adder                                                                  \
    {                                                                                    \
    public:                                                                              \
        suite##_adder()                                                                  \
        {                                                                                \
            Chimer::TestFramework::GetDriver().AddTestSuite(&suite);                     \
        }                                                                                \
    };                                                                                   \
    static suite##_adder suite##_adderInstance