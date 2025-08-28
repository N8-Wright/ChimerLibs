#pragma once
#include "TestSuite.hpp"

#include <string>
#include <string_view>
#include <optional>
#include <sstream>
#include <cstring>
namespace Chimer::TestFramework
{
	class Test
	{
		std::string m_testClass;
		std::string m_testName;
		bool m_failed;
		std::string m_failedReason;

		void MarkFailed(std::string reason);

	public:
		Test(std::string_view testClass, std::string_view testName);
		virtual ~Test() = default;
		bool Failed() const noexcept;

		std::string_view Reason() const noexcept;
		std::string_view TestClass() const noexcept;
		std::string_view TestName() const noexcept;

		virtual void Run() = 0;

		template<typename T, typename U>
		bool AssertEqImpl(const T& lhs, const U& rhs)
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
					MarkFailed(failure.str());
					return false;
				}

				return true;
			}
			else
			{
				if (lhs != rhs)
				{
					std::stringstream failure;
					failure << lhs << " does not equal " << rhs;
					MarkFailed(failure.str());
					return false;
				}

				return true;
			}
		}
	};
}

#define ASSERT_EQ(lhs, rhs) \
	if (!AssertEqImpl(lhs, rhs)) return

#define TEST(category, testName) \
	class category##_##testName : public Chimer::TestFramework::Test \
	{ \
	public: \
		category##_##testName() \
			: Chimer::TestFramework::Test(#category, #testName) \
		{ \
		} \
		void Run() override; \
	}; \
	class category##_##testName##_adder \
	{ \
	public: \
		category##_##testName##_adder() \
		{ \
			category.AddTest(std::make_unique<category##_##testName>()); \
		} \
	}; \
	static category##_##testName##_adder category##_##testName##_adderInstance; \
	void category##_##testName::Run()