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
		std::vector<std::unique_ptr<Test>> m_tests;
		std::shared_ptr<Logging::Logger> m_logger;
	public:
		TestSuite(std::shared_ptr<Logging::Logger> logger);
		void AddTest(std::unique_ptr<Test> test);
		int Run(int argc, const char** argv);
	};
}

#define TEST_SUITE(suite) \
	static Chimer::TestFramework::TestSuite suite(std::make_shared<Chimer::Logging::ConsoleLogger>(Chimer::Logging::LogLevel::Info))