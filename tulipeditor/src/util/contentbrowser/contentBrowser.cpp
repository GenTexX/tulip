#include "contentBrowser.h"

#include <logging\logger.h>
#include <imgui\imguiTulip.h>
#include "../iconProvider.h"

#include "../../global/global.h"

namespace tulip {

	ContentBrowserFile::ContentBrowserFile(ContentBrowser& browser, const std::filesystem::directory_entry& p) : ContentBrowserElement(m_browser) {
		m_type = ContentBrowserFileType::UNKNOWN;
		m_name = p.path().filename().string();
	}

	ContentBrowserFile::~ContentBrowserFile() {
	}

	bool ContentBrowserFile::render() {
		bool dir_change = false;
		
		Ref<Texture> icon = IconProvider::get()->getIcon(m_type);
		uint64_t textureID = icon->rendererID();

		ImGui::BeginGroup();
		ImGui::Dummy({ 10, 10 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() / 2 - 64 / 2);

		if (ImGui::ImageButton((void*)textureID, ImVec2{ 64, 64 }, { 0, 0 }, { 1, 1 }, 0, { 0, 0, 0, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f })) {
			
		}
		ImGui::PopStyleColor();
		bool changeText = false;
		while (ImGui::CalcTextSize((m_name + (changeText ? "..." : "")).c_str() ).x + 20 > ImGui::GetColumnWidth()) {
			m_name = m_name.substr(0, m_name.length() - 1);
			changeText = true;
		}
		if (changeText)
		{
			m_name = m_name + "...";
		}
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() / 2 - ImGui::CalcTextSize(m_name.c_str()).x / 2);
		ImGui::Text(m_name.c_str());
		ImGui::EndGroup();

		return dir_change;
	}

	ContentBrowser::ContentBrowser(const std::string& dir) {
		m_current_dir = dir;

		for (auto& p : std::filesystem::directory_iterator(m_current_dir)) {
			std::string path = p.path().string();
			if (!p.is_directory()) {
				Ref<ContentBrowserElement> element = createRef<ContentBrowserFile>(*this, p);
				m_elements.push_back(element);
			} else {
				Ref<ContentBrowserElement> element = createRef<ContentBrowserDirectory>(*this, p);
				m_elements.push_back(element);
			}
		}

	}

	ContentBrowser::~ContentBrowser() {
	}

	void ContentBrowser::render() {
		if (ImGuiTulip::ButtonDark(" ..", false)) {
			m_current_dir = std::filesystem::path(m_current_dir).parent_path().string();
			m_elements.clear();
			for (auto& p : std::filesystem::directory_iterator(m_current_dir)) {
				std::string path = p.path().string();
				if (!p.is_directory()) {
					Ref<ContentBrowserElement> element = createRef<ContentBrowserFile>(*this, p);
					m_elements.push_back(element);
				} else {
					Ref<ContentBrowserElement> element = createRef<ContentBrowserDirectory>(*this, p);
					m_elements.push_back(element);
				}
			}
		}

		ImGuiTulip::pushFont(NOTO_SANS_REGULAR, 1);

		int columns = (int)ImGui::GetContentRegionAvail().x / 128;
		if (columns == 0) columns++;
		ImGui::Columns(columns, NULL, false);
		for (Ref<ContentBrowserElement> p : m_elements) {
			
			if (p->getType() == FOLDER) {
				if (p->render()) {
					ImGui::Columns(1);
					ImGuiTulip::popFont();
					m_elements.clear();
					for (auto& p : std::filesystem::directory_iterator(m_current_dir)) {
						std::string path = p.path().string();
						if (!p.is_directory()) {
							Ref<ContentBrowserElement> element = createRef<ContentBrowserFile>(*this, p);
							m_elements.push_back(element);
						} else {
							Ref<ContentBrowserElement> element = createRef<ContentBrowserDirectory>(*this, p);
							m_elements.push_back(element);
						}
					}
					return;
				}
				ImGui::NextColumn();
			}
		}

		for (Ref<ContentBrowserElement> p : m_elements) {
			if (p->getType() != FOLDER) {
				p->render();
				ImGui::NextColumn();
			}
		}
		ImGui::Columns(1);
		ImGuiTulip::popFont();

	}

	ContentBrowserDirectory::ContentBrowserDirectory(ContentBrowser& browser, const std::filesystem::directory_entry& p) : ContentBrowserElement(browser) {
		m_name = p.path().filename().string();
		m_path = p.path().string();
		m_type = ContentBrowserFileType::FOLDER;
	}

	ContentBrowserDirectory::~ContentBrowserDirectory() {
	}

	bool ContentBrowserDirectory::render() {
		bool dir_change = false;
		TULIP_CORE_INFO(m_name);
		Ref<Texture> icon = IconProvider::get()->getIcon(m_type);
		uint64_t textureID = icon->rendererID();

		ImGui::BeginGroup();
		ImGui::Dummy({ 10, 10 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() / 2 - 64 / 2);

		if (ImGui::ImageButton(m_path.c_str(), (void*)textureID, ImVec2{ 64, 64 }, { 0, 0 }, { 1, 1 }, { 0, 0, 0, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f })) {
			m_browser.m_current_dir = m_path;
			dir_change = true;
		}
		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() / 2 - ImGui::CalcTextSize(m_name.c_str()).x / 2);
		ImGui::Text(m_name.c_str());
		ImGui::EndGroup();
		return dir_change;
	}

}