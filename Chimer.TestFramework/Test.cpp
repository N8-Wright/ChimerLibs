#include "Test.hpp"
#include <vector>

namespace Chimer::TestFramework
{
	Test::Test(std::string_view testName)
		: m_testName(testName), m_failed(false)
	{
	}

	void Test::MarkFailed(std::string reason, const std::source_location location)
	{
		m_failed = true;
		m_failedReason = std::move(reason);
		m_failedLocation = location;
	}

	bool Test::Failed() const noexcept
	{
		return m_failed;
	}

	std::string_view Test::Reason() const noexcept
	{
		return m_failedReason;
	}

	std::string_view Test::TestName() const noexcept
	{
		return m_testName;
	}

	TestFailureResult Test::GetFailureResult() const
	{
		return { m_testName, m_failedReason, m_failedLocation };
	}
}
