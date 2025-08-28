#pragma once

#include <string>

namespace Chimer::TestFramework
{
	struct TestFailureResult
	{
		std::string TestName;
		std::string Reason;
	};
}