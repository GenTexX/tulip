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

		static void init() { s_instance->initImpl(); }

		static void clearColorBufferBit() { s_instance->clearColorBufferBitImpl(); }
		static void clearDepthBufferBit() { s_instance->clearDepthBufferBitImpl(); }
		static void clearStencilBufferBit() { s_instance->clearStencilBufferBitImpl(); }
		static void setClearColor(const float& red, const float& green, const float& blue, const float& alpha) { s_instance->setClearColorImpl(red, green, blue, alpha); }
		static void setClearColor(const float& red, const float& green, const float& blue) { s_instance->setClearColorImpl(red, green, blue, 1.0f); }
		static void setClearColor(const glm::vec4& color) { s_instance->setClearColorImpl(color.x, color.y, color.z, color.w); }
		static void setClearColor(const glm::vec3& color) { s_instance->setClearColorImpl(color.x, color.y, color.z, 1.0f); }

		//Scene
		static void beginScene(const glm::mat4& camera_transform, const glm::mat4& camera_projection) { s_instance->beginSceneImpl(camera_transform, camera_projection); }
		static void endScene() { s_instance->endSceneImpl(); }

		//Draw Quad
		static void drawEditorQuad(const glm::mat4& model, const glm::vec4& color, bool selected = false) { s_instance->drawEditorQuadImpl(model, color, selected); }
		static void drawEditorQuad(const glm::mat4& model, const glm::vec4& color, RendererID sprite_id, bool selected = false) { s_instance->drawEditorQuadImpl(model, color, sprite_id, selected); }

	protected:
		virtual void initImpl() = 0;
		virtual void clearColorBufferBitImpl() const = 0;
		virtual void clearDepthBufferBitImpl() const = 0;
		virtual void clearStencilBufferBitImpl() const = 0;
		virtual void setClearColorImpl(const float&, const float&, const float&, const float&) const = 0;

		//Scene
		virtual void beginSceneImpl(const glm::mat4& camera_transform, const glm::mat4& camera_projection) = 0;
		virtual void endSceneImpl() = 0;

		//Draw Quad
		virtual void drawEditorQuadImpl(const glm::mat4& model, const glm::vec4& color, bool selected) = 0;
		virtual void drawEditorQuadImpl(const glm::mat4& transform, const glm::vec4& color, RendererID texture_id, bool selected) = 0;

	private:
		static GAPI s_graphicsAPI;
		static UniqueRef<GraphicsAPI> s_instance;
		static UniqueRef<GraphicsAPI> create();

	};

}