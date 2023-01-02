#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace tulip {

	static const float FACTOR = 2.0f * (float)M_PI / 360.0f;

	struct TransformComponent {
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		operator glm::mat4() { return getTransform(); }
		operator const glm::mat4() const { return getTransform(); }

		glm::mat4 getTransform() const {
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.x * FACTOR, { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), rotation.y * FACTOR, { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), rotation.z * FACTOR, { 0.0f, 0.0f, 1.0f });

			return glm::translate(glm::mat4(1.0f), translation) * rot * glm::scale(glm::mat4(1.0f), scale);
		}

		glm::vec3 translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	};

}