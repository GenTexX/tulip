#include "tulippch.h"
#include "framebuffer.h"

#include <graphicsapi\gAPI.h>
#include <graphicsapi\opengl\framebuffer\openGLFramebuffer.h>

namespace tulip {

    Ref<Framebuffer> Framebuffer::create(const FramebufferSpec& spec) {
		switch (GraphicsAPI::getGraphicsAPI())
		{
		case GAPI::GAPI_OPENGL:
			return createRef<OpenGLFramebuffer>(spec);

		default:
			break;
		}

		return createRef<OpenGLFramebuffer>(spec);
    }

}