#pragma once

#include "Logger.hpp"

#include <functional>

namespace Chimer::Logging
{
	template <typename T>
	concept DerivedFromLogger = std::is_base_of_v<Logger, T>;

	template <typename T, typename... GenArgs>
	class LoggerDelegate
	{
	public:
		using LogGenerator = std::function<T(GenArgs...)>;

		LoggerDelegate(LogLevel logLevel, LogGenerator logGenerator)
			: m_logLevel(logLevel), m_logGenerator(std::move(logGenerator))
		{
		}

		template <DerivedFromLogger TLogger, typename... Args>
		inline void operator()(const TLogger& logger, Args&&... args) const
		{
			if (m_level <= logger.GetLogLevel())
			{
				logger.Log(m_level, m_logGenerator(std::forward<Args>(args)...));
			}
		}

		template <DerivedFromLogger TLogger, typename... Args>
		inline void operator()(const std::shared_ptr<TLogger>& logger, Args&&... args) const
		{
			operator()(*logger, std::forward<Args>(args)...);
		}

		template <DerivedFromLogger TLogger, typename... Args>
		inline void operator()(const std::unique_ptr<TLogger>& logger, Args&&... args) const
		{
			operator()(*logger, std::forward<Args>(args)...);
		}
	private:
		LogLevel m_logLevel;
		LogGenerator m_logGenerator;
	};
}