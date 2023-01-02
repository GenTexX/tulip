#pragma once

#define COLOR_PRIMARY 0
#define COLOR_PRIMARY_HOVER 1
#define COLOR_PRIMARY_ACTIVE 2
#define COLOR_SECONDARY 3
#define COLOR_SECONDARY_HOVER 4
#define COLOR_SECONDARY_ACTIVE 5
#define COLOR_LIGHT 6
#define COLOR_LIGHT_HOVER 7
#define COLOR_LIGHT_ACTIVE 8
#define COLOR_DARK 9
#define COLOR_DARK_HOVER 10
#define COLOR_DARK_ACTIVE 11
#define COLOR_SUCCESS 12
#define COLOR_SUCCESS_HOVER 13
#define COLOR_SUCCESS_ACTIVE 14
#define COLOR_DANGER 15
#define COLOR_DANGER_HOVER 16
#define COLOR_DANGER_ACTIVE 17
#define COLOR_WARNING 18
#define COLOR_WARNING_HOVER 19
#define COLOR_WARNING_ACTIVE 20

#include <glm.hpp>

namespace tulip {

	enum class ElementSize {
		SMALL, MEDIUM, LARGE
	};

	struct ImGuiTheme {

		glm::vec4 colors[21];

		//BUTTON
		float button_rounding = 0.0;

	};
}