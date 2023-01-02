#include "tulippch.h"
#include "openGLFramebuffer.h"

#include <logging\logger.h>

#include <GL/glew.h>

namespace tulip {

	static GLenum textureTarget(bool multisampled) {
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void createTextures(bool multisampled, uint32_t* outID, uint32_t count) {
		glCreateTextures(textureTarget(multisampled), count, outID);
	}

	static void bindTexture(bool multisampled, uint32_t id) {
		glBindTexture(textureTarget(multisampled), id);
	}

	static void attachColorTexture(uint32_t id, uint32_t samples, GLenum format, uint32_t width, uint32_t height, uint32_t index) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), id, 0);
	}

	static void attachDepthTexture(uint32_t id, uint32_t samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		} else {
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), id, 0);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec) {
		this->m_spec = spec;
		this->m_id = 0;
		for (auto texture : m_spec.attachments.textures) {
			if (texture.textureFormat == FramebufferTextureFormat::DEPTH24STENCIL8)
				m_DepthAttachmentSpec = texture;
			else
				m_colorAttachmentSpecs.emplace_back(texture);

		}

		this->validate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer() {
		glDeleteFramebuffers(1, &m_id);
		glDeleteTextures((GLsizei)m_colorAttachments.size(), m_colorAttachments.data());
		m_colorAttachments.clear();
		glDeleteTextures(1, &m_depthAttachment);
		m_depthAttachment = 0;
	}

	void OpenGLFramebuffer::resize(const glm::vec2& size) {
		m_spec.width = (uint32_t)size.x;
		m_spec.height = (uint32_t)size.y;
		m_valid = false;
	}

	void OpenGLFramebuffer::bind() const {
		if (!m_valid) {
			TULIP_CORE_ERROR("ERROR: Invalid Framebuffer bound!");
			return;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);
		glViewport(0, 0, this->m_spec.width, this->m_spec.height);
	}

	void OpenGLFramebuffer::unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	const uint32_t OpenGLFramebuffer::getColorAttachmentRendererID(const uint32_t index) const {
		if (index >= m_colorAttachments.size())	{
			return m_depthAttachment;
		}
		return this->m_colorAttachments[index];
	}

	const uint32_t OpenGLFramebuffer::getDepthAttachmentRendererID() const {
		return this->m_depthAttachment;
	}

	void OpenGLFramebuffer::validate() {
		if (!m_valid)
		{
			if (m_id) {
				glDeleteFramebuffers(1, &m_id);
				glDeleteTextures((GLsizei)m_colorAttachments.size(), m_colorAttachments.data());
				m_colorAttachments.clear();
				glDeleteTextures(1, &m_depthAttachment);
				m_depthAttachment = 0;
			}

			glGenFramebuffers(1, &(this->m_id));
			glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);

			bool multisampled = m_spec.samples > 1;

			if (m_colorAttachmentSpecs.size()) {
				m_colorAttachments.resize(m_colorAttachmentSpecs.size());
				createTextures(multisampled, m_colorAttachments.data(), (uint32_t)m_colorAttachmentSpecs.size());

				for (uint32_t i = 0; i < m_colorAttachments.size(); i++) {
					bindTexture(multisampled, m_colorAttachments[i]);
					switch (m_colorAttachmentSpecs[i].textureFormat) {
					case FramebufferTextureFormat::RGBA8:
						attachColorTexture(m_colorAttachments[i], m_spec.samples, GL_RGBA8, m_spec.width, m_spec.height, i);
						break;
					default:
						break;

					}
				}
			}

			if (m_DepthAttachmentSpec.textureFormat != FramebufferTextureFormat::NONE) {
				createTextures(multisampled, &(m_depthAttachment), 1);
				bindTexture(multisampled, m_depthAttachment);
				switch (m_DepthAttachmentSpec.textureFormat) {
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					attachDepthTexture(m_depthAttachment, m_spec.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_spec.width, m_spec.height);
					break;
				default:
					break;

				}
			}

			if (m_colorAttachments.size() > 1) {
				if (m_colorAttachments.size() > 6) {
					TULIP_CORE_ERROR("ERROR: Maximum of 6 color attachments maximum exceeded! ({} color-attachments)", m_colorAttachments.size());
				}

				GLenum buffers[6] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 };
				glDrawBuffers((GLsizei)m_colorAttachments.size(), buffers);
			} else if (m_colorAttachments.empty()) {
				glDrawBuffers(GL_NONE, nullptr);
			}

			auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
				TULIP_CORE_ERROR("ERROR: Failed to create Framebuffer! Errorcode: {}", fboStatus);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			m_valid = true;
		}
	}

}