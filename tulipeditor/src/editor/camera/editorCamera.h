#pragma once

#include <render/camera.h>

namespace tulip {

	enum class EditorCameraProjectionMode {
		ORTHOGRAPHIC = 1, PERSPECTIVE = 2
	};

	class EditorCamera : public Camera {
	public:
		EditorCamera(EditorCameraProjectionMode mode = EditorCameraProjectionMode::ORTHOGRAPHIC, float zoom = 1.0f, float aspect_ratio = 16.0f/9.0f);

		virtual void onViewResize(const glm::vec2& view_size);
		void zoom(float zoom_delta);
	private:
		EditorCameraProjectionMode m_projection_mode;
		float m_zoom_level;
		float m_aspect_ratio;

	};

}