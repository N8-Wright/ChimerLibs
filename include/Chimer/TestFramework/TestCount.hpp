#pragma once

#include <ostream>

namespace Chimer::TestFramework
{
    class TestCount
    {
        size_t m_count{ 0 };

    public:
        TestCount& operator++();
        void operator+=(TestCount other);
        friend std::ostream& operator<<(std::ostream& os, const TestCount& count);
        [[nodiscard]] size_t Count() const noexcept;
    };
}