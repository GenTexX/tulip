#pragma once
#include <profiling/timer.h>

#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#define PROFILING
#ifdef PROFILING
#define TULIP_PROFILE_FUNTION() tulip::Timer timer##__LINE__(__FUNCSIG__)
#define TULIP_PROFILE_SCOPE(name) tulip::Timer timer##__LINE__(name)
#else
#define TULIP_PROFILE_FUNTION()
#define TULIP_PROFILE_SCOPE(name)
#endif

namespace tulip {

	class Profiler {
	public:
		Profiler() {}
		~Profiler() {}

		void add(const std::string& name, float result) {
			m_results[name] = result;
		}

		void clear() {
			m_results.clear();
		}

		std::vector<std::pair<const std::string, float>> get() {
			std::vector<std::pair<const std::string, float>> results;
			for (auto result : m_results) {
				results.push_back(result);
			}

			clear();

			return results;
		}

	private:
		std::unordered_map<std::string, float> m_results;
	};

}