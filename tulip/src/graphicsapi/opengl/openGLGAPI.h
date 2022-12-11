#pragma once

#include <graphicsapi\gAPI.h>
#include <render\buffer.h>

#include <GL\glew.h>

namespace tulip {

	

	class OpenGL : public GraphicsAPI {
	public:
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
		virtual void clearColorBufferBitImpl() const;
		virtual void clearDepthBufferBitImpl() const;
		virtual void setClearColorImpl(const float&, const float&, const float&, const float&) const;

	private:

	};

}