#include "tulippch.h"
#include "openGLGAPI.h"
#include <GL\glew.h>

namespace tulip {

	void OpenGL::clearColorBufferBitImpl() const {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGL::clearDepthBufferBitImpl() const {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL::setClearColorImpl(const float& r, const float& g, const float& b, const float& a) const {
		glClearColor(r, g, b, a);
	}

}
