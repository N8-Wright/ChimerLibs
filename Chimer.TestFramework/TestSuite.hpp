#pragma once
#include "Chimer.Logging/Logger.hpp"
#include "Chimer.Logging/ConsoleLogger.hpp"

#include <vector>
#include <memory>
namespace Chimer::TestFramework
{
	class Test;
	class TestSuite
	{
		std::string m_name;
		std::vector<std::unique_ptr<Test>> m_tests;
		std::shared_ptr<Logging::Logger> m_logger;
	public:
		TestSuite(std::string_view name, std::shared_ptr<Logging::Logger> logger);
		void AddTest(std::unique_ptr<Test> test);
		int Run(int argc, const char** argv);
	};
}

#define TEST_SUITE_DECLARE(suite) \
	extern Chimer::TestFramework::TestSuite suite;

#define TEST_SUITE_DEFINE(suite) \
	Chimer::TestFramework::TestSuite suite(#suite, std::make_shared<Chimer::Logging::ConsoleLogger>(Chimer::Logging::LogLevel::Info))