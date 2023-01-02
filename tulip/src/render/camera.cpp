#include "tulippch.h"
#include "camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace tulip {

	OrthoCamera::OrthoCamera(const float projection_width, const glm::vec2& view_size) : m_projection_width(projection_width) {
		float ratio = (view_size.x / view_size.y) * 0.5f;
		m_projection = glm::ortho(projection_width * -0.5f, projection_width * 0.5f, projection_width * ratio, projection_width * ratio * -1.0f, 0.1f, 10.0f);
	}

	OrthoCamera::~OrthoCamera() {
	
	}

	void OrthoCamera::onViewResize(const glm::vec2& view_size) {
		float ratio = (view_size.y / view_size.x) * 0.5f;
		m_projection = glm::ortho(m_projection_width * -0.5f, m_projection_width * 0.5f, m_projection_width * ratio, m_projection_width * ratio * -1.0f, 0.1f, 10.0f);

	}

}