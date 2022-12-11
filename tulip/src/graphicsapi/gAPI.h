#pragma once
#include <core\core.h>
#include <glm.hpp>

namespace tulip {

	enum GAPI {
		GAPI_NONE = 0,
		GAPI_OPENGL = 1,
		GAPI_VULKAN = 2,
		GAPI_DIRECTX = 3
	};

	class GraphicsAPI {
	public:
		GraphicsAPI() = default;
		virtual   ~GraphicsAPI() {}

		static const GAPI& getGraphicsAPI() { return s_graphicsAPI; }

		static void clearColorBufferBit() { s_instance->clearColorBufferBitImpl(); }
		static void clearDepthBufferBit() { s_instance->clearDepthBufferBitImpl(); }
		static void setClearColor(const float& red, const float& green, const float& blue, const float& alpha) { s_instance->setClearColorImpl(red, green, blue, alpha); }
		static void setClearColor(const float& red, const float& green, const float& blue) { s_instance->setClearColorImpl(red, green, blue, 1.0f); }
		static void setClearColor(const glm::vec4& color) { s_instance->setClearColorImpl(color.x, color.y, color.z, color.w); }
		static void setClearColor(const glm::vec3& color) { s_instance->setClearColorImpl(color.x, color.y, color.z, 1.0f); }

	protected:
		virtual void clearColorBufferBitImpl() const = 0;
		virtual void clearDepthBufferBitImpl() const = 0;
		virtual void setClearColorImpl(const float&, const float&, const float&, const float&) const = 0;

	private:
		static GAPI s_graphicsAPI;
		static UniqueRef<GraphicsAPI> s_instance;
		static UniqueRef<GraphicsAPI> create();

	};

}