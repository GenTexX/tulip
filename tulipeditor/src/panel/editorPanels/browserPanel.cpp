#include "browserPanel.h"

#include <imgui/imguiTulip.h>

#include <filesystem>
#include <format>
namespace tulip {
	const char* s_AssetDir = ".\\assets";

	BrowserPanel::BrowserPanel() : m_browser(std::filesystem::current_path().string() + "\\assets\\scenes") {
		
	}

	BrowserPanel::~BrowserPanel() {
	}


	void BrowserPanel::onImGuiRender() {
		ImGui::Begin("Asset Browser");

		;
		ImGui::Text("%s", std::filesystem::absolute(std::filesystem::directory_entry(m_browser.getCurrentDir()).path()).string().c_str());

		m_browser.render();
		
		if (ImGuiTulip::ButtonPrimary("Open Scene..."))
			Platform::openFile("Tulip Scene (*.tulipscene)\0*.tulipscene\0");
		ImGui::End();
	}

}