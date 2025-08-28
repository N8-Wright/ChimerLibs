#include "Test.hpp"
#include <vector>

namespace Chimer::TestFramework
{
	Test::Test(std::string_view category, std::string_view testName)
		: m_category(category), m_name(testName), m_failed(false)
	{
	}

	void Test::MarkFailed(std::string reason)
	{
		m_failed = true;
		m_failedReason = std::move(reason);
	}

	bool Test::Failed() const noexcept
	{
		return m_failed;
	}

	std::string_view Test::Reason() const noexcept
	{
		return m_failedReason;
	}
}
