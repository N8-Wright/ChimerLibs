#include "Test.hpp"
#include <vector>

namespace Chimer::TestFramework
{
	Test::Test(std::string_view testClass, std::string_view testName)
		: m_testClass(testClass), m_testName(testName), m_failed(false)
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

	std::string_view Test::TestClass() const noexcept
	{
		return m_testClass;
	}

	std::string_view Test::TestName() const noexcept
	{
		return m_testName;
	}
}
