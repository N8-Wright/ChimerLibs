#include "Chimer/TestFramework/TestException.hpp"

namespace Chimer::TestFramework
{
    TestException::TestException(std::string_view error,
                                 std::string_view testName,
                                 const std::source_location sourceLocation) :
        std::runtime_error(error.data()), m_testName(testName), m_sourceLocation(sourceLocation)
    {
    }
    const std::string& TestException::GetTestName() const noexcept
    {
        return m_testName;
    }

    const std::source_location& TestException::GetSourceLocation() const noexcept
    {
        return m_sourceLocation;
    }
}