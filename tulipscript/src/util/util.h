#pragma once

#include <stdint.h>

namespace tulip {

	enum class Accessibility : uint8_t {
		NONE = 0,
		PRIVATE = (1 << 0),
		INTERNAL = (1 << 1),
		PROTECTED = (1 << 2),
		PUBLIC = (1 << 3),
	};


}