#include "test_run_context.hpp"

namespace chimer::test
{
	void test_run_context::mark_failed(std::string reason)
	{
		m_failedReason = std::move(reason);
		m_passed = false;
	}

	void test_run_context::mark_passed()
	{
		m_passed = true;
	}
}
