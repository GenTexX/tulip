#include "tulippch.h"
#include "vertexArray.h"

#include <graphicsapi\opengl\openGLVertexArray.h>
#include <graphicsapi\gAPI.h>

namespace tulip {

    Ref<VertexArray> VertexArray::create() {
        switch (GraphicsAPI::getGraphicsAPI())
        {
        case GAPI::GAPI_NONE:
        case GAPI::GAPI_OPENGL:
            return createRef<OpenGLVertexArray>();
        default:
            break;
        }

        return createRef<OpenGLVertexArray>();
    }

}