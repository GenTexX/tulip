#pragma once

#include <string>

namespace tulip {

	struct TagComponent {
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& other) : tag(other) {}

		std::string tag;
	};

}