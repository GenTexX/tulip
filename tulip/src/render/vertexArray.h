#pragma once

#include <render\buffer.h>

#include <vector>

namespace tulip {

	class VertexArray {
	public:
		VertexArray() = default;
		~VertexArray() {}

		static Ref<VertexArray> create();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(Ref<VertexBuffer> vbo) = 0;
		virtual void setIndexBuffer(Ref<IndexBuffer> ibo) = 0;

		Ref<IndexBuffer> getIndexBuffer() const { return this->m_indexBuffer; }

	protected:
		std::vector<Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;

	private:

	};

}