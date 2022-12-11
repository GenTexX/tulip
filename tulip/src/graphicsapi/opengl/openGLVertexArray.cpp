#include "tulippch.h"
#include "openGLVertexArray.h"

#include <graphicsapi\opengl\openGLGAPI.h>

#include <GL\glew.h>

tulip::OpenGLVertexArray::OpenGLVertexArray() {
	glGenVertexArrays(1, &(this->m_id));
}

tulip::OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &(this->m_id));
}

void tulip::OpenGLVertexArray::bind() const {
	glBindVertexArray(this->m_id);
}

void tulip::OpenGLVertexArray::unbind() const {
	glBindVertexArray(NULL);
}

void tulip::OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer> vbo) {
	this->bind();
	vbo->bind();

	uint32_t index = 0;
	const BufferLayout& layout = vbo->getLayout();

	for (const auto& element : layout) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.getComponentSize(), OpenGL::bufferElementTypeToGLenum(element.m_Type), element.m_Normalized, layout.getStride(), (void*)(element.m_Offset));
		++index;
	}

	this->m_vertexBuffers.push_back(vbo);
}

void tulip::OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer> ibo) {
	this->bind();
	ibo->bind();

	this->m_indexBuffer = ibo;
}
