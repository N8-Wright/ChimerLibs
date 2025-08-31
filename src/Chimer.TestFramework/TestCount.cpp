#include "Chimer.TestFramework/TestCount.hpp"

#include <ostream>

namespace Chimer::TestFramework
{
    TestCount& TestCount::operator++()
    {
        m_count++;
        return *this;
    }

    void TestCount::operator+=(const TestCount other)
    {
        m_count += other.m_count;
    }

    std::ostream& operator<<(std::ostream& os, const TestCount& count)
    {
        return os << count.m_count;
    }

    size_t TestCount::Count() const noexcept
    {
        return m_count;
    }
}