#include "tulippch.h"
#include "buffer.h"
#include <graphicsapi\gAPI.h>
#include <graphicsapi\opengl\openGLBuffer.h>

namespace tulip {

    Ref<IndexBuffer> tulip::IndexBuffer::create(uint32_t* data, uint32_t size) {
        switch (GraphicsAPI::getGraphicsAPI())
        {
        case GAPI::GAPI_NONE:
        case GAPI::GAPI_OPENGL:
            return createRef<OpenGLIndexBuffer>(data, size);
        default:
            break;
        }

        return createRef<OpenGLIndexBuffer>(data, size);
    }

    Ref<VertexBuffer> VertexBuffer::create(float* data, uint32_t size) {
        switch (GraphicsAPI::getGraphicsAPI())
        {
        case GAPI::GAPI_NONE:
        case GAPI::GAPI_OPENGL:
            return createRef<OpenGLVertexBuffer>(data, size);
        default:
            break;
        }

        return createRef<OpenGLVertexBuffer>(data, size);
    }

}