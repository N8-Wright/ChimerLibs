#pragma once
#include "../Core/Concepts.hpp"

#include "Chimer/TestFramework/TestSuite.hpp"
#include "Chimer/TestFramework/TestFailureResult.hpp"
#include "Chimer/TestFramework/TestDriver.hpp"

#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>
#include <cstring>
#include <source_location>

namespace Chimer::TestFramework
{
    template<typename T>
    std::string FormatValue(const T& value)
    {
        if constexpr (Streamable<T>)
        {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
        else
        {
            // Fallback for non-streamable types
            return "<unprintable>";
        }
    }

    class Test
    {
        std::string m_testName;
        bool m_failed;
        std::string m_failedReason;
        std::source_location m_failedLocation;

    public:
        explicit Test(std::string_view testName);
        virtual ~Test() = default;
        [[nodiscard]] bool Failed() const noexcept;
        void MarkFailed(std::string reason, const std::source_location& location);

        [[nodiscard]] std::string_view Reason() const noexcept;
        [[nodiscard]] std::string_view TestName() const noexcept;
        [[nodiscard]] TestFailureResult GetFailureResult() const;

        virtual void Run() = 0;

        template<typename T, typename U>
        bool AssertNotEqual(const T& lhs,
                            const U& rhs,
                            const std::source_location location = std::source_location::current())
        {
            using TL = std::decay_t<T>;
            using TR = std::decay_t<U>;
            constexpr bool isCString =
                (std::is_same_v<TL, const char*> && std::is_same_v<TR, const char*>) ||
                (std::is_array_v<T> && std::is_array_v<U> &&
                 std::is_same_v<std::remove_extent_t<T>, char> &&
                 std::is_same_v<std::remove_extent_t<U>, char>);

            if constexpr (isCString)
            {
                if (std::strcmp(lhs, rhs) == 0)
                {
                    std::stringstream failure;
                    failure << "\"" << lhs << "\" equals \"" << rhs << "\" when it should not";
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else if constexpr (requires { lhs != rhs; })
            {
                if (lhs == rhs)
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " equals " << FormatValue(rhs) << " when it should not";
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else
            {
                static_assert(false, "Cannot compare these types");
                return false;
            }
        }

        template<typename T, typename U>
        bool AssertEqual(const T& lhs,
                         const U& rhs,
                         const std::source_location location = std::source_location::current())
        {
            using TL = std::decay_t<T>;
            using TR = std::decay_t<U>;
            constexpr bool isCString =
                (std::is_same_v<TL, const char*> && std::is_same_v<TR, const char*>) ||
                (std::is_array_v<T> && std::is_array_v<U> &&
                 std::is_same_v<std::remove_extent_t<T>, char> &&
                 std::is_same_v<std::remove_extent_t<U>, char>);

            if constexpr (isCString)
            {
                if (std::strcmp(lhs, rhs) != 0)
                {
                    std::stringstream failure;
                    failure << "\"" << lhs << "\" does not equal \"" << rhs << "\"";
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else if constexpr (requires { lhs != rhs; })
            {
                if (lhs != rhs)
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " does not equal " << FormatValue(rhs);
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else
            {
                static_assert(false, "Cannot compare these types");
                return false;
            }
        }

        template<typename T, typename U>
        bool AssertGreaterThan(const T& lhs,
                               const U& rhs,
                               const std::source_location location = std::source_location::current())
        {
            if constexpr (requires { lhs > rhs; })
            {
                if (!(lhs > rhs))
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " is not greater than " << FormatValue(rhs);
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else
            {
                static_assert(false, "Cannot compare these types");
                return false;
            }
        }

        template<typename T, typename U>
        bool AssertLessThan(const T& lhs,
                            const U& rhs,
                            const std::source_location location = std::source_location::current())
        {
            if constexpr (requires { lhs < rhs; })
            {
                if (!(lhs < rhs))
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " is not less than " << FormatValue(rhs);
                    MarkFailed(failure.str(), location);
                    return false;
                }

                return true;
            }
            else
            {
                static_assert(false, "Cannot compare these types");
                return false;
            }
        }
    };
}

#define ASSERT_FALSE(expr)                                                                    \
    if (expr)                                                                                 \
    {                                                                                         \
        MarkFailed("Expression was not false: '" #expr "'", std::source_location::current()); \
        return;                                                                               \
    }
#define ASSERT_TRUE(expr)                                                                    \
    if (!(expr))                                                                             \
    {                                                                                        \
        MarkFailed("Expression was not true: '" #expr "'", std::source_location::current()); \
        return;                                                                              \
    }

#define ASSERT_GT(lhs, rhs)           \
    if (!AssertGreaterThan(lhs, rhs)) \
    return

#define ASSERT_LT(lhs, rhs)        \
    if (!AssertLessThan(lhs, rhs)) \
    return

#define ASSERT_NOT_EQ(lhs, rhs)    \
    if (!AssertNotEqual(lhs, rhs)) \
    return

#define ASSERT_EQ(lhs, rhs)     \
    if (!AssertEqual(lhs, rhs)) \
    return

#define TEST(testClass, testName)                                                 \
    class testClass##_##testName : public Chimer::TestFramework::Test             \
    {                                                                             \
    public:                                                                       \
        testClass##_##testName() : Chimer::TestFramework::Test(#testName)         \
        {                                                                         \
        }                                                                         \
        void Run() override;                                                      \
    };                                                                            \
    class testClass##_##testName##_adder                                          \
    {                                                                             \
    public:                                                                       \
        testClass##_##testName##_adder()                                          \
        {                                                                         \
            testClass.AddTest(std::make_unique<testClass##_##testName>());        \
        }                                                                         \
    };                                                                            \
    static testClass##_##testName##_adder testClass##_##testName##_adderInstance; \
    void testClass##_##testName::Run()