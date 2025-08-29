#pragma once

#include <string>
#include <source_location>

namespace Chimer::TestFramework
{
	struct TestFailureResult
	{
		std::string TestName;
		std::string Reason;
		std::source_location Location;
	};
}