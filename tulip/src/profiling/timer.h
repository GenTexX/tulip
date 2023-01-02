#pragma once
#include <logging/logger.h>

#include <chrono>



namespace tulip {

	class Timer {
	public:
		Timer(const std::string& name) : m_name(name) { m_start = std::chrono::high_resolution_clock::now(); }
		~Timer() { stop(); }

		void stop();

	private:
		const std::string m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};

}