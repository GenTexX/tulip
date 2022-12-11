#pragma once

#include <render\vertexArray.h>

namespace tulip {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void bind() const;
		virtual void unbind() const;

		virtual void addVertexBuffer(Ref<VertexBuffer> vbo);
		virtual void setIndexBuffer(Ref<IndexBuffer> ibo);

	private:
		uint32_t m_id;
	};

}