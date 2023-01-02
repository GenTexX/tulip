#pragma once

#include <glm.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/access.hpp>

namespace tulip {


	class Camera {
	public:
		Camera() : m_projection(glm::mat4(1.0f)) {}

		const glm::mat4& getProjection() { return m_projection; }

		virtual void onViewResize(const glm::vec2& view_size) = 0;

		template <class Archive>
		void serialize(Archive& ar) {
			ar(cereal::make_nvp("last_projection", m_projection));
		}

	protected:
		glm::mat4 m_projection;
	};

	class OrthoCamera : public Camera {
	public:
		OrthoCamera() :m_projection_width(0.0f) {}
		OrthoCamera(const float projection_width, const glm::vec2& view_size);
		~OrthoCamera();

		virtual void onViewResize(const glm::vec2& view_size) override;
	private:
		float m_projection_width;

		friend class cereal::access;
		template <class Archive>
		void serialize(Archive& ar) {
			ar(cereal::make_nvp("camera", cereal::base_class<Camera>(this)), cereal::make_nvp("projection_width", m_projection_width));
		}

	};

}