#pragma once
#include "Chimer.TestFramework/TestFailureResult.hpp"
#include "Chimer.TestFramework/TestCount.hpp"

#include <vector>
namespace Chimer::TestFramework
{
    struct TestSuiteResult
    {
        TestCount Passed;
        TestCount Failed;
        std::vector<TestFailureResult> FailedTests;
    };
}