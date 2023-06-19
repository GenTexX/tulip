#pragma once

#include <core/core.h>

#include <glm.hpp>
#include <string>

namespace tulip {

	enum TextureMinMagFilter {
		LINEAR = 1,
		NEAREST = 2
	};

	enum TextureFormat {
		NONE = 0, RGBA8 = 1, RGB8 = 2
	};

	enum TextureType {
		TEXTURE_2D = 1, TEXTURE_3D = 2
	};

	struct TextureSpecification {
		std::string path;
		TextureType texture_type;
		TextureFormat texture_format;
		TextureMinMagFilter texture_min_mag_filter;
		boolean flip;

	};

	class Texture {
	public:
		Texture() = default;
		virtual ~Texture() {};

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual glm::vec2 getSize() = 0;

		RendererID rendererID() { return m_id; }

		static Ref<Texture> create(TextureSpecification spec);

		virtual const char* path() { return m_spec.path.c_str(); };
		virtual TextureType type() { return m_spec.texture_type; }
		virtual TextureFormat format() { return m_spec.texture_format; }
		virtual TextureMinMagFilter minMagFilter() { return m_spec.texture_min_mag_filter; }
		virtual const TextureSpecification& getSpec() { return m_spec; }

		virtual void path(const std::string& path) { m_spec.path = path; }
		virtual void type(TextureType type) { m_spec.texture_type = type; }
		virtual void format(TextureFormat format) { m_spec.texture_format = format; }
		virtual void minMagFilter(TextureMinMagFilter filter) { m_spec.texture_min_mag_filter = filter; }

		virtual void reload() = 0;

		virtual bool valid() = 0;

	protected:
		RendererID m_id;
		uint32_t m_width;
		uint32_t m_height;
		TextureSpecification m_spec;
	};

}