#pragma once

#include <render\framebuffer.h>

#include <glm.hpp>

namespace tulip {

	

	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		~OpenGLFramebuffer();
		virtual void resize(const glm::vec2& size) override;
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual const uint32_t getColorAttachmentRendererID(const uint32_t index) const;
		virtual const uint32_t getDepthAttachmentRendererID() const;
		virtual void validate() override;
	private:
		uint32_t m_id;
		std::vector<uint32_t> m_colorAttachments;
		uint32_t m_depthAttachment;

		std::vector<FramebufferTextureSpecification> m_colorAttachmentSpecs;
		FramebufferTextureSpecification m_DepthAttachmentSpec;


	};

}