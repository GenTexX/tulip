#include <logging\logger.h>
#include <window\window.h>
#include <platform\platform.h>
#include <graphicsapi\gAPI.h>
#include <render\buffer.h>
#include <render\vertexArray.h>
#include <shader\shader.h>
#include <core\core.h>
#include <event\event.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <GL\glew.h>
#define _USE_MATH_DEFINES
#include <math.h>

static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* param) {

	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;	//ignore useless stuff :)

	std::cout << "OpenGL ERROR " << message << " [";

	switch (source) {
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API, "; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System, "; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler, "; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party, "; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application, "; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other, "; break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error, "; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour, "; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour, "; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability, "; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance, "; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker, "; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group, "; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group, "; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other, "; break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	}

	std::cout << "]" << std::endl;
}

void myEventCallback(tulip::Event& e) {

	TULIP_TRACE("{}", e.toString());

}


int main() {

	tulip::Logger::init();
	std::shared_ptr<tulip::Window> window = tulip::Window::create(800, 600, "Testwindow Nr. 2", 500, 200);

	window->setEventCallback(myEventCallback);

	TULIP_TRACE("Window Size: ({}, {})", window->getWidth(), window->getHeight());
	TULIP_TRACE("Window Position: ({}, {})", window->getPosX(), window->getPosY());;
	TULIP_TRACE("Window Title: {}", window->getTitle());

	if (glewInit() != GLEW_OK) {
		TULIP_ERROR("Failed to initialize GLEW!");
	}

	tulip::GraphicsAPI::setClearColor(0.2f, 0.6f, 0.4f, 1.0f);
	
	float vert[4 * 4] = {

		/*######## COORDS ########*/
		-0.5f,	-0.5f,  0.0f,  1.0f,
		 0.5f,	-0.5f,  0.0f,  1.0f,
		 0.5f,	 0.5f,  0.0f,  1.0f,
		-0.5f,	 0.5f,  0.0f,  1.0f

	};

	uint32_t ind[6] = { 0, 1, 2, 0, 2, 3 };

	TULIP_INFO("Size of vert: {}", sizeof(vert));
	TULIP_INFO("Size of ind: {}", sizeof(ind));

	auto vbo = tulip::VertexBuffer::create(vert, sizeof(vert));
	auto ibo = tulip::IndexBuffer::create(ind, sizeof(ind));

	tulip::BufferLayout layout = { { tulip::BufferElementType::Float4, "coords" } };
	vbo->setLayout(layout);

	auto vao = tulip::VertexArray::create();
	vao->addVertexBuffer(vbo);
	vao->setIndexBuffer(ibo);
	  
	glDebugMessageCallback(debugCallback, NULL);

	auto shader = tulip::Shader::create();
	shader->readFile("./res/shader/basic.tulipshader");
	shader->compile();
	glm::mat4 view = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	glm::mat4 projection = glm::perspective((float)M_PI * 0.4f, (float)window->getWidth()/ (float)window->getHeight(), 0.1f, 100.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -5.0));

	int i = 0;
	while (!window->shouldClose()) {
		tulip::GraphicsAPI::clearColorBufferBit();
		tulip::GraphicsAPI::clearDepthBufferBit();

		shader->bind();

		shader->setMat4("u_View", view);
		shader->setMat4("u_Projection", projection);
		shader->setMat4("u_Model", model);
		shader->setFloat4("u_Color", glm::vec4(0.84f, 0.27f, 0.33f, 1.0f));

		vao->bind();
		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);

		window->update();
		i++;
	}

	return 0;

}
