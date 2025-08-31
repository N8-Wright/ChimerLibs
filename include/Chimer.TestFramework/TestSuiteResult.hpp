#pragma once
#include "Chimer.TestFramework/TestFailureResult.hpp"
#include "Chimer.TestFramework/TestCount.hpp"

namespace Chimer::TestFramework
{
    struct TestSuiteResult
    {
        TestCount Passed;
        TestCount Failed;
        std::vector<TestFailureResult> FailedTests;
    };
}