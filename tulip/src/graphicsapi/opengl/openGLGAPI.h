#pragma once

#include <graphicsapi\gAPI.h>
#include <render\buffer.h>
#include <render\vertexArray.h>
#include <shader\shader.h>

#include <GL\glew.h>

namespace tulip {

	

	class OpenGL : public GraphicsAPI {
	public:
		OpenGL();
		virtual ~OpenGL();

		static GLenum bufferElementTypeToGLenum(BufferElementType type) {

			switch (type)
			{
			case BufferElementType::None:	break;
			case BufferElementType::Float1:
			case BufferElementType::Float2:
			case BufferElementType::Float3:
			case BufferElementType::Float4:
			case BufferElementType::Mat2:
			case BufferElementType::Mat3:
			case BufferElementType::Mat4:	return GL_FLOAT;
			case BufferElementType::Int1:
			case BufferElementType::Int2:
			case BufferElementType::Int3:
			case BufferElementType::Int4:	return GL_INT;
			case BufferElementType::Bool1:	return GL_BOOL;
			default: break;
			}

			TULIP_CORE_ERROR("ERROR: Unkonwn Buffer-Element-Type!");
			return 0;

		}
	protected:
		virtual void initImpl();
		virtual void clearColorBufferBitImpl() const;
		virtual void clearDepthBufferBitImpl() const;
		virtual void clearStencilBufferBitImpl() const;
		virtual void setClearColorImpl(const float&, const float&, const float&, const float&) const;

		//Scene
		virtual void beginSceneImpl(const glm::mat4& camera_transform, const glm::mat4& camera_projection);
		virtual void endSceneImpl();

		//Draw Quad
		virtual void drawEditorQuadImpl(const glm::mat4& transform, const glm::vec4& color, bool selected) override;
		virtual void drawEditorQuadImpl(const glm::mat4& transform, const glm::vec4& color, RendererID texture_id, bool selected) override;

	private:
		glm::mat4 m_scene_view;
		glm::mat4 m_scene_projection;

		Ref<VertexArray> m_flat_color_vao;
		Ref<VertexArray> m_sprite_vao;
		Ref<Shader> m_flat_color_shader;
		Ref<Shader> m_sprite_shader;

	};

}