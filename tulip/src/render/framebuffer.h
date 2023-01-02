#pragma once

#include <core/core.h>

#include <glm.hpp>

namespace tulip {

	enum class FramebufferTextureFormat {

		NONE = 0,
		RGBA8,
		DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification {
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) : textureFormat(format) {}

		FramebufferTextureFormat textureFormat;

	};

	struct FramebufferAttachmentSpecification {
		
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification> attachments) : textures(attachments) {}
		
		std::vector<FramebufferTextureSpecification> textures;

	};

	struct FramebufferSpec {
		uint32_t width, height;
		uint32_t samples = 1;
		FramebufferAttachmentSpecification attachments;
	};

	class Framebuffer {
	public:
		Framebuffer() = default;
		virtual ~Framebuffer() {}

		virtual void resize(const glm::vec2& size) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const uint32_t getColorAttachmentRendererID(const uint32_t index) const = 0;
		virtual const uint32_t getDepthAttachmentRendererID() const = 0;

		static Ref<Framebuffer> create(const FramebufferSpec& spec);
		virtual void validate() = 0;

	protected:
		FramebufferSpec m_spec;
		bool m_valid = false;


	private:
	};

}