#pragma once
#include <core/core.h>
#include <render/camera.h>

namespace tulip {

	struct CameraComponent {
		CameraComponent() {}
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(Ref<Camera> cam) : m_camera(cam) {}

		void onViewResize(const glm::vec2& view_size) { m_camera->onViewResize(view_size); }

		operator const glm::mat4& () { return m_camera->getProjection(); }

		Ref<Camera> m_camera;
	};

}