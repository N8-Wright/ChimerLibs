#pragma once
#include "test.hpp"

#include <vector>
namespace chimer::test
{
	/// <summary>
	/// A suite of tests that can be run independently.
	/// </summary>
	class suite
	{
		std::vector<test> m_tests;
	};
}