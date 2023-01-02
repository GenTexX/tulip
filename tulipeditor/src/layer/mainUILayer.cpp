#include "mainUILayer.h"

#include "../panel/editorPanels/sceneHierarchyPanel.h"
#include "../panel/editorPanels/entityDetailsPanel.h"
#include "../panel/editorPanels/browserPanel.h"
#include "../panel/editorPanels/profilingPanel.h"

namespace tulip {

	MainUILayer::MainUILayer(Ref<GlobalManager> global) :m_global(global) {
		
	}

	MainUILayer::~MainUILayer() {
	}

	void MainUILayer::onAttach() {
		m_panels.emplace_back(createRef<SceneHierarchyPanel>(m_global));
		m_panels.emplace_back(createRef<EntityDetailsPanel>(m_global));
		m_panels.emplace_back(createRef<BrowserPanel>());
		m_panels.emplace_back(createRef<ProfilingPanel>());
	}

	void MainUILayer::onDetach() {
	}

	void MainUILayer::onUpdate(const float& delta) {
	}

	void MainUILayer::onEvent(Event& e) {
	}

	void MainUILayer::onImGuiRender() {

		for (auto panel : m_panels) {
			panel->onImGuiRender();
		}


	}
}