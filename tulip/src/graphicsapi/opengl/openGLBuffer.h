#pragma once
#include <render/buffer.h>

namespace tulip {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* data, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const;
		virtual void setLayout(const BufferLayout&);

		virtual float* map() const override;
		virtual void unmap() const override;


	private:
		uint32_t m_id;
		BufferLayout m_layout;

	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t* map() const override;
		virtual void unmap() const override;


	private:
		uint32_t m_id;

	};

}