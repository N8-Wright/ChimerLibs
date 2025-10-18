#pragma once
#include "Chimer/Core/Concepts.hpp"

#include "Chimer/TestFramework/TestSuite.hpp"
#include "Chimer/TestFramework/TestFailureResult.hpp"
#include "Chimer/TestFramework/TestDriver.hpp"
#include "Chimer/TestFramework/TestException.hpp"

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

    public:
        explicit Test(std::string_view testName);
        virtual ~Test() = default;
        [[nodiscard]] std::string_view TestName() const noexcept;

        virtual void Run() = 0;

        template<typename T, typename U>
        void AssertNotEqual(const T& lhs,
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
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else if constexpr (requires { lhs != rhs; })
            {
                if (lhs == rhs)
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " equals " << FormatValue(rhs) << " when it should not";
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else
            {
                static_assert(false, "Cannot compare these types");
            }
        }

        template<typename TException, typename TAction>
            requires CallableWith<TAction, TException>
        void AssertExceptionIs(const std::exception_ptr exceptionPtr, TAction&& action, const std::source_location location = std::source_location::current())
        {
            if (!exceptionPtr)
            {
                throw TestException("Provided exception pointer was null", m_testName, location);
            }

            try
            {
                std::rethrow_exception(exceptionPtr);
            }
            catch (const TException& exception)
            {
                action(exception);
                return;
            }
            catch (...)
            {
            }

            throw TestException("Exception was not of expected type", m_testName, location);
        }

        template<Callable TAction>
        std::exception_ptr AssertThrows(TAction&& action,
                                        const std::source_location location = std::source_location::current())
        {
            try
            {
                action();
            }
            catch (...)
            {
                return std::current_exception();
            }

            throw TestException("Action did not result in an exception", m_testName, location);
        }

        template<typename T, typename U>
        void AssertEqual(const T& lhs,
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
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else if constexpr (requires { lhs != rhs; })
            {
                if (lhs != rhs)
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " does not equal " << FormatValue(rhs);
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else
            {
                static_assert(false, "Cannot compare these types");
            }
        }

        template<typename T, typename U>
        void AssertGreaterThan(const T& lhs,
                               const U& rhs,
                               const std::source_location location = std::source_location::current())
        {
            if constexpr (requires { lhs > rhs; })
            {
                if (!(lhs > rhs))
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " is not greater than " << FormatValue(rhs);
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else
            {
                static_assert(false, "Cannot compare these types");
            }
        }

        template<typename T, typename U>
        void AssertLessThan(const T& lhs,
                            const U& rhs,
                            const std::source_location location = std::source_location::current())
        {
            if constexpr (requires { lhs < rhs; })
            {
                if (!(lhs < rhs))
                {
                    std::stringstream failure;
                    failure << FormatValue(lhs) << " is not less than " << FormatValue(rhs);
                    throw TestException(failure.str(), m_testName, location);
                }
            }
            else
            {
                static_assert(false, "Cannot compare these types");
            }
        }

        template<Callable TExpr>
        void AssertTrue(TExpr&& expr, const std::source_location location = std::source_location::current())
        {
            if (!expr())
            {
                throw TestException("Expression was not true", m_testName, location);
            }
        }

        template<typename TExpr>
        void AssertTrue(TExpr&& expr, const std::source_location location = std::source_location::current())
        {
            if (!expr)
            {
                throw TestException("Expression was not true", m_testName, location);
            }
        }

        template<Callable TExpr>
        void AssertFalse(TExpr&& expr, const std::source_location location = std::source_location::current())
        {
            if (expr())
            {
                throw TestException("Expression was not false", m_testName, location);
            }
        }

        template<typename Expr>
        void AssertFalse(Expr&& expr, const std::source_location location = std::source_location::current())
        {
            if (expr)
            {
                throw TestException("Expression was not false", m_testName, location);
            }
        }
    };
}

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