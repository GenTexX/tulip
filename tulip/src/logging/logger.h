#pragma once
#include <core/core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace tulip {

	class Logger {
	public:
		static void init();

		static Ref<spdlog::logger> getCoreLogger();
		static Ref<spdlog::logger> getAppLogger();
		static Ref<spdlog::logger> getFileLogger();

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_AppLogger;
		static Ref<spdlog::logger> s_FileLogger;

	};

}

#define TULIP_CORE_TRACE(...) tulip::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define TULIP_CORE_INFO(...) tulip::Logger::getCoreLogger()->info(__VA_ARGS__)
#define TULIP_TRACE(...) tulip::Logger::getAppLogger()->trace(__VA_ARGS__)
#define TULIP_INFO(...) tulip::Logger::getAppLogger()->info(__VA_ARGS__)

#define TULIP_CORE_WARN(...) tulip::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define TULIP_CORE_ERROR(...) tulip::Logger::getCoreLogger()->error(__VA_ARGS__)
#define TULIP_CORE_CRITICAL(...) tulip::Logger::getCoreLogger()->critical(__VA_ARGS__)

#define TULIP_WARN(...) tulip::Logger::getAppLogger()->warn(__VA_ARGS__)
#define TULIP_ERROR(...) tulip::Logger::getAppLogger()->error(__VA_ARGS__)
#define TULIP_CRITICAL(...) tulip::Logger::getAppLogger()->critical(__VA_ARGS__)

#define TULIP_LOG(...) tulip::Logger::getFileLogger()->trace(__VA_ARGS__)
