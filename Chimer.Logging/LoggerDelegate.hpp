#pragma once

#include "Logger.hpp"

#include <functional>
#include <string>
#include <string_view>

namespace Chimer::Logging
{
	template <typename T>
	concept DerivedFromLogger = std::is_base_of_v<Logger, T>;

	// Helper to extract function signature from a lambda
	template <typename T>
	struct LambdaTraits;

	template <typename R, typename... Args>
	struct LambdaTraits<R(*)(Args...)>
	{
		using ReturnType = R;
		using ArgsTuple = std::tuple<Args...>;
	};

	template <typename R, typename... Args>
	struct LambdaTraits<std::function<R(Args...)>>
	{
		using ReturnType = R;
		using ArgsTuple = std::tuple<Args...>;
	};

	// NOTE: The unary + operator on a lambda converts it to a function pointer if possible.
	// See: https://stackoverflow.com/questions/70505162/why-would-one-want-to-put-a-unary-plus-operator-in-front-of-a-c-lambda
	template <typename Lambda>
	struct LambdaTraits : LambdaTraits<decltype(+std::declval<Lambda>())> {};

	template <typename TGeneratedLog, typename TLogLambda, typename... TGenArgs>
	class LoggerDelegate2
	{
	public:

		LoggerDelegate2(LogLevel logLevel, TLogLambda&& logGenerator)
			: m_logLevel(logLevel), m_logGenerator(std::move(logGenerator))
		{
		}

		template <DerivedFromLogger TLogger, typename... TArgs>
		inline void operator()(const TLogger& logger, TArgs&&... args) const
		{
			if (logger.ConfiguredToLog(m_logLevel))
			{
				logger.Log(m_logLevel, m_logGenerator(std::forward<TArgs>(args)...));
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
		TLogLambda m_logGenerator;
	};

	template <typename Lambda>
	auto MakeLoggerDelegate2(LogLevel level, Lambda&& lambda)
	{
		using Traits = LambdaTraits<std::decay_t<Lambda>>;
		using ReturnType = typename Traits::ReturnType;
		using ArgsTuple = typename Traits::ArgsTuple;

		return[&]<std::size_t... I>(std::index_sequence<I...>)
		{
			using DecayedLambda = std::decay_t<Lambda>;
			return LoggerDelegate2<
				ReturnType,
				DecayedLambda,
				std::tuple_element_t<I, ArgsTuple>...
			>(
				level,
				std::forward<Lambda>(lambda)
			);
		}(std::make_index_sequence<std::tuple_size_v<ArgsTuple>>{});
	}
}