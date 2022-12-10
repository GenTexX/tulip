#include "tulippch.h"
#include "logger.h"

namespace tulip {


	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

	void Logger::init() {
	
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("TULIP");
		s_CoreLogger->set_level(spdlog::level::trace);
	
		s_AppLogger = spdlog::stdout_color_mt("APPLICATION");
		s_AppLogger->set_level(spdlog::level::trace);
	}
	Ref<spdlog::logger> Logger::getCoreLogger() {
		return Logger::s_CoreLogger;
	}
	Ref<spdlog::logger> Logger::getAppLogger() {
		return Logger::s_AppLogger;
	}
}

