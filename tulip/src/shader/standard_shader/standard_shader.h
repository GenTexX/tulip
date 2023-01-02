#pragma once

namespace tulip {

	const char* OGL_TULIP_SPRITE_SHADER = "";
	const char* OGL_TULIP_FLAT_COLOR_SHADER =	"#shader vertex\n"
												"#version 410\n"
												"layout(location = 0) in vec4 vertexPosition_modelspace;\n"
												"uniform mat4 u_Model;\n"
												"uniform mat4 u_View;\n"
												"uniform mat4 u_Projection;\n"
												"void main() {\n"
												"	vec4 vertexPosition_worldSpace = u_Model * vertexPosition_modelspace;\n"
												"	gl_Position = u_Projection * (u_View * vertexPosition_worldSpace);\n"
												"}\n"
												"#shader fragment\n"
												"	#version 410\n"
												"	layout(location = 0) out vec4 color;\n"
												"layout(location = 1) out vec4 texcord;\n"
												"uniform vec4 u_Color;\n"
												"void main() {\n"
												"	color = u_Color;\n"
												"	texcord = vec4(0.0, 0.0, 0.0, 1.0);\n"
												"}";

}