#pragma once
#include <core\core.h>

namespace tulip {

	class Platform {
	public:
		Platform() = default;
		Platform(const Platform&) = delete;
		Platform& operator=(const Platform&) = delete;

		virtual ~Platform() {}

		
		static float getTime() { return s_instance->getTimeImpl(); }
	
	protected:
		virtual float getTimeImpl() const = 0;
	
	private:
		static UniqueRef<Platform> create();
		static UniqueRef<Platform> s_instance;

	};

}