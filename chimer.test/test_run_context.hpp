#pragma once
#include <optional>
#include <string>

namespace chimer::test
{
	class test_run_context
	{
		/// <summary>
		/// After a test has been run this will be set to either true or false.
		/// Before a test is run this value is not filled in.
		/// </summary>
		std::optional<bool> m_passed;

		/// <summary>
		/// The reason the test failed. This usually will contain the assertion logic
		/// that did not succeed.
		/// </summary>
		std::string m_failedReason;

	public:
		void mark_failed(std::string reason);
		void mark_passed();
	};
}