#include "tulippch.h"
#include "openGLTexture.h"

#include <logging/logger.h>
#include <stb_image.h>
#include <GL/glew.h>

namespace tulip {

	static TextureFormat getTextureFormatFromChannels(int channels) {
		if (channels == 3) return TextureFormat::RGB8;
		if (channels == 3) return TextureFormat::RGBA8;
		return TextureFormat::NONE;
	}

	static int getChannelsOfTexureFormat(TextureFormat format) {
		switch (format)
		{
		case tulip::NONE:
			return 0;
		case tulip::RGBA8:
			return 4;
		case tulip::RGB8:
			return 3;
		default:
			break;
		}

		return 0;

	}

	static GLenum getGLFormat(TextureFormat format, bool internal_format) {
		switch (format)
		{
		case tulip::RGBA8:
			return internal_format ? GL_RGBA8 : GL_RGBA;
		case tulip::RGB8:
			return internal_format ? GL_RGB8 : GL_RGB;
		default:
			TULIP_CORE_ERROR("ERROR: Tecture format not supported!");
			return 0;
		}

	}

	static GLenum getGLMinMagFilter(TextureMinMagFilter filter) {
		switch (filter)
		{
		case TextureMinMagFilter::LINEAR:
			return GL_LINEAR; 
		case TextureMinMagFilter::NEAREST:
				return GL_NEAREST;
		default:
			TULIP_CORE_ERROR("ERROR: Texture MinMagFilter not supported!");
			return 0;
		}
	}

	static bool createTextures(TextureSpecification spec, RendererID* id, uint32_t width, uint32_t height) {
		switch (spec.texture_type)
		{
		case TextureType::TEXTURE_2D:
			glCreateTextures(GL_TEXTURE_2D, 1, id);
			glTextureStorage2D(*id, 1, getGLFormat(spec.texture_format, true), width, height);
			break;
		case TextureType::TEXTURE_3D:
		default:
			TULIP_CORE_ERROR("ERROR: Texture type not supported!");
			return false;
		}

		return false;
	}

	OpenGLTexture::OpenGLTexture(TextureSpecification spec) {
		m_spec = spec;
		m_valid = false;

		reload();
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &m_id);
	}

	void OpenGLTexture::bind() {
		glBindTextureUnit(0, m_id);
	}

	void OpenGLTexture::unbind() {
	}

	glm::vec2 OpenGLTexture::getSize() {
		return glm::vec2();
	}

	void OpenGLTexture::reload() {
		if(m_valid)
			glDeleteTextures(1, &m_id);

		m_valid = false;
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		auto data = stbi_load(m_spec.path.c_str(), &width, &height, &channels, 0);
		if (!data) {
			TULIP_CORE_ERROR("ERROR: Failed to load {}", m_spec.path);
			return;
		} else {
			if (m_spec.texture_format == TextureFormat::NONE) {
				m_spec.texture_format = getTextureFormatFromChannels(channels);
				if (m_spec.texture_format == TextureFormat::NONE) {
					TULIP_CORE_ERROR("ERROR: {} has unsupported format", m_spec.path);
					return;
				}
			}
			if (channels != getChannelsOfTexureFormat(m_spec.texture_format)) {
				TULIP_CORE_ERROR("ERROR: {} is not in the right format", m_spec.path);
				m_spec.texture_format = getTextureFormatFromChannels(channels);
				if (m_spec.texture_format == TextureFormat::NONE) {
					TULIP_CORE_ERROR("ERROR: {} has unsupported format", m_spec.path);
					return;
				}
			}

			m_width = width;
			m_height = height;

			createTextures(m_spec, &m_id, m_width, m_height);

			auto filter = getGLMinMagFilter(m_spec.texture_min_mag_filter);
			glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filter);
			glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filter);

			//FIXXX ME:		change for 3d???
			glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, getGLFormat(m_spec.texture_format, false), GL_UNSIGNED_BYTE, data);

			m_valid = true;
			stbi_image_free(data);
		}

	}

}