#include "Chimer/TestFramework/Test.hpp"
#include <vector>

namespace Chimer::TestFramework
{
    Test::Test(const std::string_view testName) :
        m_testName(testName)
    {
    }

    std::string_view Test::TestName() const noexcept
    {
        return m_testName;
    }
}
