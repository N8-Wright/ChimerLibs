#pragma once

#include "Chimer.Logging/Logger.hpp"

#include <vector>

#include <gsl/gsl>

namespace Chimer::TestFramework
{
    class TestSuite;
    class TestDriver
    {
        std::vector<TestSuite*> m_suites;
        std::shared_ptr<Logging::Logger> m_logger;

    public:
        explicit TestDriver(gsl::not_null<std::shared_ptr<Logging::Logger>> logger);
        void AddTestSuite(gsl::not_null<TestSuite*> suite);
        int Run(int argc, const char** argv);
    };

    TestDriver& GetDriver();
    int RunAllTests(int argc, const char** argv);
}
