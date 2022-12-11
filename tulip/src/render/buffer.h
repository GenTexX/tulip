#pragma once

#include <logging\logger.h>
#include <core\core.h>

#include <cstdint>
#include <vector>

namespace tulip {

	enum class BufferElementType {
		None = 0,
		Float1, Float2, Float3, Float4,
		Mat2, Mat3, Mat4,
		Int1, Int2, Int3, Int4,
		Bool1
	};

	static uint32_t getBufferElementTypeSize(BufferElementType type) {

		switch (type)
		{
		case BufferElementType::None:	break;
		case BufferElementType::Float1:	return sizeof(float);
		case BufferElementType::Float2:	return sizeof(float) * 2;
		case BufferElementType::Float3:	return sizeof(float) * 3;
		case BufferElementType::Float4:	return sizeof(float) * 4;
		case BufferElementType::Mat2:	return sizeof(float) * 2 * 2;
		case BufferElementType::Mat3:	return sizeof(float) * 3 * 3;
		case BufferElementType::Mat4:	return sizeof(float) * 4 * 4;
		case BufferElementType::Int1:	return sizeof(int);
		case BufferElementType::Int2:	return sizeof(int) * 2;
		case BufferElementType::Int3:	return sizeof(int) * 3;
		case BufferElementType::Int4:	return sizeof(int) * 4;
		case BufferElementType::Bool1:	return sizeof(bool);
		default: break;
		}

		TULIP_CORE_ERROR("ERROR: Unkonwn Buffer-Element-Type!");
		return 0;
	}

	class Buffer {
	public:
		Buffer() = default;
		virtual ~Buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		const uint32_t& getSize() const { return this->m_size; }

	protected:
		uint32_t m_size = 0;

	};

	struct BufferElement {
		std::string m_ElementName;
		BufferElementType m_Type;
		uint32_t m_Size;
		size_t m_Offset;
		bool m_Normalized;

		BufferElement() = default;
		BufferElement(BufferElementType type, const std::string& name, const bool& normalized = false) {
			this->m_Type = type;
			this->m_ElementName = name;
			this->m_Size = getBufferElementTypeSize(type);
			this->m_Offset = 0;
			this->m_Normalized = normalized;
		}

		virtual ~BufferElement() {}

		uint32_t getComponentSize() const {

			switch (this->m_Type)
			{
			case BufferElementType::None:	break;
			case BufferElementType::Float1:	return 1;
			case BufferElementType::Float2:	return 2;
			case BufferElementType::Float3:	return 3;
			case BufferElementType::Float4:	return 4;
			case BufferElementType::Mat2:	return 2 * 2;
			case BufferElementType::Mat3:	return 3 * 3;
			case BufferElementType::Mat4:	return 4 * 4;
			case BufferElementType::Int1:	return 1;
			case BufferElementType::Int2:	return 2;
			case BufferElementType::Int3:	return 3;
			case BufferElementType::Int4:	return 4;
			case BufferElementType::Bool1:	return 1;
			default:
				break;
			}

			return 0;

		}

	};

	class BufferLayout {
	public:
		BufferLayout() { this->m_Stride = 0; }
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {

			size_t offset = 0;
			this->m_Stride = 0;

			for (auto& element : this->m_Elements) {

				element.m_Offset = offset;
				offset += element.m_Size;
				this->m_Stride += element.m_Size;

			}

		}

		~BufferLayout() {};

		const std::vector<BufferElement>& getElements() const { return this->m_Elements; }
		const uint32_t& getStride() const { return this->m_Stride; };

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	};

	class VertexBuffer : public Buffer {
	public:
		VertexBuffer() {}
		virtual ~VertexBuffer() {}

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout&) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual float* map() const = 0;
		virtual void unmap() const = 0;

		static Ref<VertexBuffer> create(float* data, uint32_t size);

	};

	class IndexBuffer : public Buffer {

	public:
		IndexBuffer() {}
		virtual ~IndexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t* map() const = 0;
		virtual void unmap() const = 0;

		static Ref<IndexBuffer> create(uint32_t* data, uint32_t size);


	};

}