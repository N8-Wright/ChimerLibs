#pragma once
#include "TestSuite.hpp"

#include <string>
#include <string_view>
#include <optional>
#include <sstream>

namespace Chimer::TestFramework
{
	class Test
	{
		std::string m_category;
		std::string m_name;
		bool m_failed;
		std::string m_failedReason;

		void MarkFailed(std::string reason);

	public:
		Test(std::string_view category, std::string_view testName);
		virtual ~Test() = default;
		bool Failed() const noexcept;
		std::string_view Reason() const noexcept;

		virtual void Run() = 0;

		template<typename T, typename U>
		bool AssertEqImpl(const T& lhs, const U& rhs)
		{
			if (lhs != rhs)
			{
				std::stringstream failure;
				failure << lhs << " does not equal " << rhs;
				MarkFailed(failure.str());
				return false;
			}
			else
			{
				return true;
			}
		}
	};
}

#define CHIMER_ASSERT_EQ(lhs, rhs) \
	if (!AssertEqImpl(lhs, rhs)) return

#define CHIMER_TEST(category, testName) \
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