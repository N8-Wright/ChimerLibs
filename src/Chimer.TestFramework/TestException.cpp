#include "Chimer/TestFramework/TestException.hpp"

namespace Chimer::TestFramework
{
    TestException::TestException(std::string_view error, const std::source_location sourceLocation)
        : std::runtime_error(error.data()), m_sourceLocation(sourceLocation)
    {
    }

    const std::source_location& TestException::SourceLocation() const noexcept
    {
        return m_sourceLocation;
    }
}