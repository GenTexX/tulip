#include "tulippch.h"
#include "openGLBuffer.h"
#include <GL\glew.h>
namespace tulip {

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size) {
        this->m_size = size;
        glCreateBuffers(1, &(this->m_id));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_size, data, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &(this->m_id));
    }

    void OpenGLIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
    }

    void OpenGLIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    }

    uint32_t* OpenGLIndexBuffer::map() const {
        return (uint32_t*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
    }

    void OpenGLIndexBuffer::unmap() const {
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size) {
        this->m_size = size;
        glGenBuffers(1, &(this->m_id));
        glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
        glBufferData(GL_ARRAY_BUFFER, this->m_size, data, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &(this->m_id));
    }

    void OpenGLVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
    }

    void OpenGLVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, NULL);
    }

    const BufferLayout& tulip::OpenGLVertexBuffer::getLayout() const {
        return this->m_layout;
    }

    void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
        this->m_layout = layout;
    }

    float* OpenGLVertexBuffer::map() const {
        return (float*) glMapBuffer(GL_ARRAY_BUFFER, this->m_id);
    }

    void OpenGLVertexBuffer::unmap() const {
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

}