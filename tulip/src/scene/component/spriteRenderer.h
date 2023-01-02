#pragma once
#include <texture/texture.h>
#include <glm.hpp>

namespace tulip {

	struct SpriteRendererComponent {
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& other) : color(other) {}

		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture> m_sprite = nullptr;
	};

}