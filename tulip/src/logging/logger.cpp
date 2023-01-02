#include "tulippch.h"
#include "logger.h"

namespace tulip {


	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_AppLogger;
	std::shared_ptr<spdlog::logger> Logger::s_FileLogger;

	void Logger::init() {
	
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("TULIP_CORE");
		s_CoreLogger->set_level(spdlog::level::trace);
	
		s_AppLogger = spdlog::stdout_color_mt("APPLICATION");
		s_AppLogger->set_level(spdlog::level::trace);

		s_FileLogger = spdlog::rotating_logger_mt("TULIP_LOGGER", "logs/tulip.log", 1048576 * 5, 3);
		s_FileLogger->set_level(spdlog::level::trace);
	}
	Ref<spdlog::logger> Logger::getCoreLogger() {
		return Logger::s_CoreLogger;
	}
	Ref<spdlog::logger> Logger::getAppLogger() {
		return Logger::s_AppLogger;
	}
	Ref<spdlog::logger> Logger::getFileLogger() {
		return Logger::s_FileLogger;
	}
}

