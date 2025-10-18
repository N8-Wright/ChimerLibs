#pragma once

#include <stdexcept>
#include <source_location>

namespace Chimer::TestFramework
{
    class TestException : public std::runtime_error
    {
        std::string m_testName;
        std::source_location m_sourceLocation;

    public:
        TestException(std::string_view error,
                      std::string_view testName,
                      std::source_location sourceLocation = std::source_location::current());

        const std::string& GetTestName() const noexcept;
        const std::source_location& GetSourceLocation() const noexcept;
    };
}