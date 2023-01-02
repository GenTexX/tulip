#pragma once
#include <core\core.h>

#include <string>

namespace tulip {

	class Platform {
	public:
		Platform() = default;
		Platform(const Platform&) = delete;
		Platform& operator=(const Platform&) = delete;

		virtual ~Platform() {}

		static std::string openFile(const char* filter) { return s_instance->openFileImpl(filter); }
		static std::string saveFile(const char* filter) { return s_instance->saveFileImpl(filter); }

		static float getTime() { return s_instance->getTimeImpl(); }
		static std::string getMainFontTTF() { return s_instance->getMainFontTTFImpl(); }
	
	protected:
		virtual float getTimeImpl() const = 0;
		virtual std::string getMainFontTTFImpl() const = 0;

		virtual const std::string openFileImpl(const char* filter) = 0;
		virtual const std::string saveFileImpl(const char* filter) = 0;

	private:
		static UniqueRef<Platform> create();
		static UniqueRef<Platform> s_instance;

	};

}