#include "tulippch.h"
#include "timer.h"

#include <application/application.h>

namespace tulip {

	void Timer::stop() {
		auto end = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();
		auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();
		auto duration = stop - start;

		Application::getProfiler().add(m_name, (float)duration * 0.001f);

	}


}