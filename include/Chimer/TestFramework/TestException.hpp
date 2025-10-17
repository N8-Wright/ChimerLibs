#pragma once

#include <stdexcept>
#include <source_location>

namespace Chimer::TestFramework
{
    class TestException : public std::runtime_error
    {
        std::source_location m_sourceLocation;

    public:
        TestException(std::string_view error, std::source_location sourceLocation = std::source_location::current());
        const std::source_location& SourceLocation() const noexcept;
    };
}