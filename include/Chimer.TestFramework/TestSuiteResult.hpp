#pragma once
#include "Chimer.TestFramework/TestFailureResult.hpp"

namespace Chimer::TestFramework
{
    struct TestSuiteResult
    {
        size_t TestsPassed;
        size_t TestsFailed;
        std::vector<TestFailureResult> FailedTests;
    };
}