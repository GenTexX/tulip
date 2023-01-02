#include "editorCamera.h"

#include <gtc/matrix_transform.hpp>

namespace tulip {
	EditorCamera::EditorCamera(EditorCameraProjectionMode mode, float zoom, float aspect_ratio) : m_projection_mode(mode), m_zoom_level(zoom), m_aspect_ratio(aspect_ratio) {
		
	}
	void EditorCamera::onViewResize(const glm::vec2& view_size) {
		m_aspect_ratio = view_size.x / view_size.y;
		switch (m_projection_mode)
		{
		case EditorCameraProjectionMode::ORTHOGRAPHIC:
			m_projection = glm::ortho(-8.0f * m_aspect_ratio * m_zoom_level, 8.0f * m_aspect_ratio * m_zoom_level, 8.0f * m_zoom_level, -8.0f * m_zoom_level, 0.1f, 100.f);
			break;
		case EditorCameraProjectionMode::PERSPECTIVE:
			m_projection = glm::perspective(1.22f, m_aspect_ratio, 100.0f, 0.1f);
			break;
		default:
			break;
		}
	}

	void EditorCamera::zoom(float zoom_delta) {
		m_zoom_level += zoom_delta;
		switch (m_projection_mode)
		{
		case EditorCameraProjectionMode::ORTHOGRAPHIC:
			m_projection = glm::ortho(-8.0f * m_aspect_ratio * m_zoom_level, 8.0f * m_aspect_ratio * m_zoom_level, 8.0f * m_zoom_level, -8.0f * m_zoom_level, 0.1f, 100.f);
			break;
		case EditorCameraProjectionMode::PERSPECTIVE:
			m_projection = glm::perspective(1.22f, m_aspect_ratio, 100.0f, 0.1f);
			break;
		default:
			break;
		}
	}
}