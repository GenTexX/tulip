#pragma once
#include <platform\platform.h>

#include <chrono>

namespace tulip {

	class PlatformWindows : public Platform {
	public:
		PlatformWindows() {
			m_startTime = std::chrono::high_resolution_clock::now();
		}
		virtual ~PlatformWindows() {}

	protected:
		virtual float getTimeImpl() const {
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds> (now - this->m_startTime).count() * 0.001f;
		}
		virtual std::string getMainFontTTFImpl() const {
			return "C:/Windows/Fonts/arial.ttf";
		}


		virtual const std::string openFileImpl(const char* filter) override;
		virtual const std::string saveFileImpl(const char* filter) override;

	private:
		std::chrono::high_resolution_clock::time_point m_startTime;
	};

}