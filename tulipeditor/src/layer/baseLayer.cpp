#include "baseLayer.h"

#include <serialization/serializer.h>

#include <tulip.h>
#include <imgui.h>

namespace tulip {

	BaseLayer::BaseLayer(Ref<GlobalManager> global) : m_global(global) {

	}

	BaseLayer::~BaseLayer() {
	}

	void BaseLayer::onAttach() {

		Serializer<Scene> scene_serializer(m_global->activeScene(), SerializationFormat::JSON);
		scene_serializer.load("assets/scenes/scene.tulipscene");

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		auto& colors = ImGui::GetStyle().Colors;

		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

		auto& rounding = ImGui::GetStyle().TabRounding;
		//rounding = 0.0f;

		m_global->loadFonts();
		ImGuiTulip::setDefaultFont(NOTO_SANS_REGULAR, 2);
		
		//Window
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		//Tab
		colors[ImGuiCol_Tab] = ImVec4{ 0.25f, 0.25f, 0.25f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.30f, 0.30f, 0.30f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.27f, 0.27f, 0.27f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.20f, 0.20f, 0.20f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.23f, 0.23f, 0.23f, 1.0f };

		//Header
		colors[ImGuiCol_Header] = ImVec4{ 0.24f, 0.24f, 0.24f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.28f, 0.28f, 0.28f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.32f, 0.32f, 0.32f, 1.0f };

		//Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.13f, 0.13f, 0.13f, 1.0f };

		//Frame
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.0f };

		//Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.0f };

		//MenuBar
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };

	}

	void BaseLayer::onDetach() {
	}

	void BaseLayer::onUpdate(const float& delta) {
	}

	void BaseLayer::onEvent(Event& e) {
	}

	void BaseLayer::onImGuiRender() {

		if (ImGui::BeginMenuBar())
		{
			ImGuiTulip::pushFont(NOTO_SANS_BOLD, 2);
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New", "")) {
					TULIP_CORE_ERROR("\"New\" is not implemented yet!");
				}
				if (ImGui::MenuItem("Open...", "")) {
					std::string filename = Platform::openFile("Tulip Scene (*.tulipscene)\0*.tulipscene\0");
					Ref<Scene> newscene = createRef<Scene>();
					Serializer<Scene> scene_serializer(newscene, SerializationFormat::JSON);
					TULIP_CORE_INFO("Trying to load {}", filename);
					scene_serializer.load(filename);
					m_global->activeScene(newscene);
					m_global->selectedEntity(Entity());
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Save", "")) {
					Serializer<Scene> scene_serializer(m_global->activeScene(), SerializationFormat::JSON);
					scene_serializer.save("assets/scenes/scene.tulipscene");
				}
				if (ImGui::MenuItem("Save as...", "")) {
					std::string filename = Platform::saveFile("Tulip Scene (*.tulipscene)\0*.tulipscene\0");
					Serializer<Scene> scene_serializer(m_global->activeScene(), SerializationFormat::JSON);
					scene_serializer.save(filename);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Not implemented yet", "")) { TULIP_INFO("Not implemented yet!"); }
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window")) {
				if (ImGui::MenuItem("Not implemented yet", "")) { TULIP_INFO("Not implemented yet!"); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help")) {
				if (ImGui::MenuItem("Not implemented yet", "")) { TULIP_INFO("Not implemented yet!"); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
			ImGuiTulip::popFont();
		}

	}

}