#include "TestSuite.hpp"
#include "Test.hpp"

#include <iostream>
namespace Chimer::TestFramework
{
	void TestSuite::AddTest(std::unique_ptr<Test> test)
	{
		m_tests.push_back(std::move(test));
	}

	int TestSuite::Run(int, const char**)
	{
		for (auto& test : m_tests)
		{
			test->Run();
			if (test->Failed())
			{
				std::cout << "Failed because " << test->Reason();
			}
		}

		return 0;
	}
}