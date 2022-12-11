#include "tulippch.h"
#include "shader.h"

#include <graphicsapi\gAPI.h>
#include <graphicsapi\opengl\openGLShader.h>

namespace tulip {

    Shader::Shader() {
    }

    Shader::~Shader() {
    }


    Ref<Shader> Shader::create() {
        switch (GraphicsAPI::getGraphicsAPI())
        {
        case GAPI::GAPI_NONE:
        case GAPI::GAPI_OPENGL:
            return createRef<OpenGLShader>();
        default:
            break;
        }

        return createRef<OpenGLShader>();
    }

}