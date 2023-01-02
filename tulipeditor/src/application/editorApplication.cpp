#include "editorApplication.h"

#include "../layer/baseLayer.h"
#include "../layer/mainUILayer.h"
#include "../layer/viewportLayer.h"

#include <serialization/serializer.h>
#include <profiling/timer.h>

#include <mono/jit/jit.h>

namespace tulip {
	EditorApplication::EditorApplication() { 
		s_instance = this; 
		m_global = createRef<GlobalManager>();
		m_global->activeScene(createRef<Scene>());
	}
	void EditorApplication::genWindow() {
		this->m_mainWindow = tulip::Window::create(1600, 900, "Tulip Editor", 200, 200);
	}

	void EditorApplication::init() {
		TULIP_PROFILE_SCOPE("Initialization");
		m_imGuiLayer = (tulip::createRef<tulip::ImGuiLayer>());
		m_imGuiLayer->setMenuBar(true);
		m_layers.pushOverlay(this->m_imGuiLayer);
		m_layers.pushLayer(tulip::createRef<BaseLayer>(m_global));
		m_layers.pushLayer(tulip::createRef<MainUILayer>(m_global));
		m_layers.pushLayer(tulip::createRef<ViewportLayer>(m_global));
	}

	void EditorApplication::run() {
		while (!this->m_mainWindow->shouldClose()) {
			this->onUpdate();
		}
	}

}