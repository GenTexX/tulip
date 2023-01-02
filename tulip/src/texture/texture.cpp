#include "tulippch.h"
#include "texture.h"

#include <graphicsapi/gAPI.h>
#include <graphicsapi/opengl/texture/openGLTexture.h>


namespace tulip {

    Ref<Texture> Texture::create(TextureSpecification spec) {
		switch (GraphicsAPI::getGraphicsAPI()) {
		case GAPI::GAPI_OPENGL:
			return createRef<OpenGLTexture>(spec);
		default:
			break;
		}

		return createRef<OpenGLTexture>(spec);

    }

}
