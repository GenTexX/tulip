#include "browserPanel.h"

#include <imgui/imguiTulip.h>

namespace tulip {

	BrowserPanel::BrowserPanel() {
	}

	BrowserPanel::~BrowserPanel() {
	}

	void BrowserPanel::onImGuiRender() {
		ImGui::Begin("Asset Browser");
		if (ImGuiTulip::ButtonPrimary("Open Scene..."))
			Platform::openFile("Tulip Scene (*.tulipscene)\0*.tulipscene\0");
		ImGui::End();
	}

}