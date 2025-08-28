#pragma once
#include "test_run_context.hpp"

#include "test_run_context.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <functional>

namespace Chimer::Test
{
	/// <summary>
	/// An individual test.
	/// </summary>
	template<typename T>
	class TestClass
	{
		std::string m_name;
	public:
		explicit TestClass(std::string_view name)
			: m_name(name)
		{
		}
	};
#define CHIMER_CLASS_BOILERPLATE(testClass) \
public: \
	testClass(std::string_view name) \
		: TestClass(name) \
	{ \
	}
#define CHIMER_REGISTER_TEST_CLASS(testClass) \
	static testClass g_chimerRegistered##testClass(#testClass)

// #define CHIMER_TEST_CLASS(testClass) \
//	class testClass : public Chimer::Test::TestClass<testClass, static_cast<const char[]>(#testClass)>
}