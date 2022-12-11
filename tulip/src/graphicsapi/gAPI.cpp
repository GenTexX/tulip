#include "tulippch.h"
#include "gAPI.h"
#include <graphicsapi\opengl\openGLGAPI.h>
#include <logging\logger.h>

namespace tulip {

	// CHOOSE GRAPHICS API HERE
	GAPI GraphicsAPI::s_graphicsAPI = GAPI::GAPI_OPENGL;

	UniqueRef<GraphicsAPI> GraphicsAPI::s_instance = GraphicsAPI::create();


	UniqueRef<GraphicsAPI> GraphicsAPI::create() {
		switch (s_graphicsAPI)
		{
		case GAPI::GAPI_NONE:
			TULIP_CORE_ERROR("ERROR: No Graphics-API selected!");
			break;
		case GAPI::GAPI_OPENGL:
			return createUniqueRef<OpenGL>();
		case GAPI::GAPI_VULKAN:
			TULIP_CORE_ERROR("ERROR: Vulkan is not supported yet!");
			break;
		case GAPI::GAPI_DIRECTX:
			TULIP_CORE_ERROR("ERROR: DirectX is not supported yet!");
			break;
		default:
			break;
		}

		return createUniqueRef<OpenGL>();

	}

}
