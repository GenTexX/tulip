#include "tulippch.h"
#include "sceneHierarchyPanel.h"

#include <imgui.h>

namespace tulip {

	void SceneHierarchyPanel::onImGuiRender() {
		ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_None);


		if (m_global->sceneValid()) {
			m_global->activeScene()->forEachEntity([&](auto entity) {
				auto& tag = entity.getComponent<TagComponent>();

				ImGuiTreeNodeFlags flags = (this->m_global->selectedEntity() == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
				bool expanded = ImGuiTulip::TreeNodePrimary(entity.id(), tag.tag.c_str(), this->m_global->selectedEntity() == entity);
				if (ImGui::BeginPopupContextItem()) {
					ImGui::MenuItem("Delete");
					if (ImGui::IsItemClicked())
					{
						m_global->activeScene()->removeEntity(entity);
						TULIP_CORE_TRACE("DELETE");

					}

					ImGui::EndPopup();
				}
				if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
					this->m_global->selectedEntity(entity);
					TULIP_CORE_INFO("Selected Entity is now {}", this->m_global->selectedEntity().getComponent<TagComponent>().tag.c_str());
				}

				if (expanded) {
					ImGui::TreePop();
				}

				});

		}

		ImGui::Dummy({ 0.0f, 20.0f });


		if (ImGuiTulip::ButtonPrimarySmall("+ Add Entity##01", true))
			m_global->activeScene()->createEntity("Empty Entity");

		if (ImGui::BeginPopup("rc_entity_menu")) {
			if (ImGui::BeginMenu("Option 1")) {

				if (ImGui::MenuItem("Sprite-Renderer")) {}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Option 2")) {

				if (ImGui::MenuItem("Sprite-Renderer")) {}

				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}



		ImGui::End();
	}

}