#include <logging\logger.h>
#include <platform\windows\window\windowsWindow.h>
#include <gl\glew.h>

int main() {

	tulip::Logger::init();
	tulip::WindowsWindow window(400, 400, "Testwindow", 400, 100);

	TULIP_TRACE("Window Size: ({}, {})", window.getWidth(), window.getHeight());
	TULIP_TRACE("Window Position: ({}, {})", window.getPosX(), window.getPosY());;
	TULIP_TRACE("Window Title: {}", window.getTitle());

	if (glewInit() != GLEW_OK) {
		TULIP_ERROR("Failed to initialize GLEW!");
	}

	glClearColor(0.45f, 0.75f, 0.95f, 1.0f);
	int i = 0;
	while (!window.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		window.update();
		i++;
	}

	return 0;

}