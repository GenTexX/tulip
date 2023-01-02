#pragma once
#include <texture/texture.h>

namespace tulip {

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(TextureSpecification spec);
		virtual ~OpenGLTexture();

		virtual void bind() override;
		virtual void unbind() override;

		virtual glm::vec2 getSize() override;

		virtual void reload() override;

		virtual bool valid() override { return m_valid; }
	private:
		bool m_valid;

	};

}