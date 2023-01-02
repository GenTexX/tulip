#include "entityDetailsPanel.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace tulip {

	static const char* linear_show_val = "Linear";
	static const char* nearest_show_val = "Nearest";

	static const char* getFilterShowValue(TextureMinMagFilter filter) {
		switch (filter)
		{
		case TextureMinMagFilter::LINEAR:
			return linear_show_val;
		case TextureMinMagFilter::NEAREST:
			return nearest_show_val;
		default:
			TULIP_CORE_WARN("Unknown MinMag-Filter! Don't know what to show in combo?!");
			break;
		}

		return "Herst oida bist deppad, oida, de filtermethode gibts goaned";
	}

	static const char* getCameraShowValue(Camera& camera) {
		auto& cam_type = typeid(camera);
		if (cam_type == typeid(OrthoCamera)) return "orthographic";

		return "Herst oida bist deppad, oida, de kamera gibts goaned";
	}

	static void drawRGBAControl(const std::string& label, glm::vec4& vec, float reset = 0.0f) {

		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.11f, 0.11f, 0.11f, 1.0f });
		if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PopStyleColor();
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::BeginTable((label + "_Color_Table").c_str(), 2);

			ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 4 * lineHeight + 16);
			ImGui::TableNextColumn();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 3.0f, 0.0f });

			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			//R Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.96f, 0.12f, 0.24f, 1.0f });
			ImGuiTulip::pushFont(NOTO_SANS_BOLD, 2);
			if (ImGui::Button("R", buttonSize))
				vec.x = reset;
			ImGuiTulip::popFont();
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##R", &(vec.x), 0.0f, 1.0f, "%.4f");
			ImGui::PopItemWidth();
			ImGui::Dummy({ 0.0f, 3.0f });

			//G Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.218f, 0.64f, 0.38f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.533f, 0.74f, 0.612f, 1.0f });
			ImGuiTulip::pushFont(NOTO_SANS_BOLD, 2);
			if (ImGui::Button("G", buttonSize))
				vec.y = reset;
			ImGui::PopFont();
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##G", &(vec.y), 0.0f, 1.0f, "%.4f");
			ImGui::PopItemWidth();
			ImGui::Dummy({ 0.0f, 3.0f });

			//B Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.218f, 0.38f, 0.64f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.533f, 0.612f, 0.74f, 1.0f });
			ImGuiTulip::pushFont(NOTO_SANS_BOLD, 2);
			if (ImGui::Button("B", buttonSize))
				vec.z = reset;
			ImGuiTulip::popFont();
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##B", &(vec.z), 0.0f, 1.0f, "%.4f");
			ImGui::PopItemWidth();
			ImGui::Dummy({ 0.0f, 3.0f });

			//A Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.38f, 0.38f, 0.38f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.533f, 0.612f, 0.74f, 1.0f });
			ImGuiTulip::pushFont(NOTO_SANS_BOLD, 2);
			if (ImGui::Button("A", buttonSize))
				vec.w = reset;
			ImGuiTulip::popFont();
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##A", &(vec.w), 0.0f, 1.0f, "%.4f");
			ImGui::PopItemWidth();
			ImGui::Dummy({ 0.0f, 3.0f });

			ImGui::PopStyleColor(8);
			ImGui::PopStyleVar();

			ImGui::TableNextColumn();

			if (ImGui::ColorButton("Color", *(ImVec4*)(&vec), ImGuiColorEditFlags_AlphaPreviewHalf, { 4 * lineHeight + 9, 4 * lineHeight + 9 })) {
				ImGui::OpenPopup("ColorPicker");
			}

			if (ImGui::BeginPopup("ColorPicker"))
			{
				ImGui::ColorPicker4("##picker", &(vec.x));
				ImGui::EndPopup();
			}
			ImGui::EndTable();

			ImGui::TreePop();
		} else
			ImGui::PopStyleColor();

	}

	static void drawVec3Control(const std::string& label, glm::vec3& vec, float reset = 0.0f) {



	}


	void EntityDetailsPanel::onImGuiRender() {

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::Begin("Details");

		ImGui::PopStyleVar(2);

		if (m_global->selectedEntity()) {

			static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;

			Entity selected = m_global->selectedEntity();

			//TagComponent
			if (ImGui::CollapsingHeader("Tag", flags)) {
				auto& tag_component = selected.getComponent<TagComponent>();
				ImGuiTulip::BeginContainer(8.0f);
				ImGuiTulip::InputText("Tag", &(tag_component.tag));
				ImGuiTulip::EndContainer();
			}

			//TransformComponent
			if (ImGui::CollapsingHeader("Transform", flags)) {
				auto& transform_component = selected.getComponent<TransformComponent>();
				ImGuiTulip::BeginContainer(8.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
				ImGuiTulip::Vector3f("Position", &transform_component.translation);
				ImGui::Dummy({ 0.0f, 4.0f });
				ImGuiTulip::Vector3f("Rotation", &transform_component.rotation);
				ImGui::Dummy({ 0.0f, 4.0f });
				ImGuiTulip::Vector3f("Scale", &transform_component.scale, 1.0f);
				ImGui::PopStyleVar();
				ImGuiTulip::EndContainer();
			}

			//SpriteRendererComponent
			if (selected.hasComponent<SpriteRendererComponent>()) {
				if (ImGui::CollapsingHeader("SpriteRenderer", flags)) {
					ImGuiTulip::BeginContainer(8.0f);
					auto& sprite_renderer_component = selected.getComponent<SpriteRendererComponent>();
					drawRGBAControl("Color", sprite_renderer_component.color);
					if (ImGui::TreeNodeEx("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
						std::string sprite_path;
						if (sprite_renderer_component.m_sprite) {
							sprite_path = sprite_renderer_component.m_sprite->path();
						};
						float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
						ImVec2 buttonSize = { lineHeight * 1.5f, lineHeight };
						auto size_avail = ImGui::GetContentRegionAvail();
						float input = size_avail.x - buttonSize.x - 10.0f;
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 10.0f, 0.0f });
						ImGui::PushItemWidth(input);
						ImGui::InputText("##LABEL", &sprite_path, ImGuiInputTextFlags_ReadOnly);
						ImGui::SameLine();
						if (ImGuiTulip::ButtonPrimary("...", false, buttonSize)) {
							std::string image_file = Platform::openFile("PNG (*.png)\0*.png\0");
							if (!image_file.empty()) {
								TULIP_CORE_TRACE("Try to load {}", image_file);
								TextureSpecification texture_spec = {};
								texture_spec.path = image_file.c_str();
								texture_spec.texture_format = TextureFormat::RGBA8;
								texture_spec.texture_min_mag_filter = TextureMinMagFilter::LINEAR;
								texture_spec.texture_type = TextureType::TEXTURE_2D;
								sprite_renderer_component.m_sprite = Texture::create(texture_spec);
								if (!sprite_renderer_component.m_sprite->valid()) {
									ImGui::OpenPopup("Texture loading failed");
								}
							}
						}
						ImGui::PopStyleVar();
						if (sprite_renderer_component.m_sprite) {

							ImGui::Dummy(ImVec2{ 0.0f, 5.0f });
							ImGui::Text("Min-Mag-Filter"); ImGui::SameLine();
							ImGui::PushItemWidth(-1);
							if (ImGui::BeginCombo("##combo_filter", getFilterShowValue(sprite_renderer_component.m_sprite->minMagFilter()), 0)) {
								if (ImGui::Selectable("Linear", sprite_renderer_component.m_sprite->minMagFilter() == TextureMinMagFilter::LINEAR)) {
									sprite_renderer_component.m_sprite->minMagFilter(TextureMinMagFilter::LINEAR);
									sprite_renderer_component.m_sprite->reload();
								}
								if (ImGui::Selectable("Nearest", sprite_renderer_component.m_sprite->minMagFilter() == TextureMinMagFilter::NEAREST)) {
									sprite_renderer_component.m_sprite->minMagFilter(TextureMinMagFilter::NEAREST);
									sprite_renderer_component.m_sprite->reload();
								}
								ImGui::EndCombo();
							}
						}
						ImGui::TreePop();
					}
					ImGuiTulip::EndContainer();
				}
			}

			if (selected.hasComponent<CameraComponent>()) {
				
				auto& camera_component = selected.getComponent<CameraComponent>();
				if (ImGui::CollapsingHeader("Camera", flags)) {
					if (ImGui::BeginCombo("##LABEL", getCameraShowValue(*camera_component.m_camera))) {
						if (ImGui::Selectable("orthographic")) {

						}

						if (ImGui::Selectable("perspective")) {

						}
						ImGui::EndCombo();
					}
					if (typeid(*camera_component.m_camera) == typeid(OrthoCamera)) {
						ImGui::Text("Orthographoc Camera");

					}
				}

			}

			if (ImGui::Button("Test")) {
				ImGui::OpenPopup("Texture loading failed");
			}

			//Righ-Click-Menu
			if (ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered()) {
				ImGui::OpenPopup("rcmenu-entity-details");
			}

			if (ImGui::BeginPopup("rcmenu-entity-details")) {
				if (ImGui::BeginMenu("Add component")) {

					if (!selected.hasComponent<SpriteRendererComponent>()) {
						if (ImGui::MenuItem("Sprite-Renderer"))
							selected.addComponent<SpriteRendererComponent>();
					}

					if (!selected.hasComponent<CameraComponent>()) {
						if (ImGui::BeginMenu("Camera")) {
							if (ImGui::MenuItem("Orthographic"))
								selected.addComponent<CameraComponent>(createRef<OrthoCamera>(16.0f, glm::vec2{ 1.0, 1.0 }));
							ImGui::EndMenu();
						}
					}

					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}

		}

		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Texture loading failed", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
			ImGui::TextColored(ImVec4{ 0.8f, 0.3f, 0.2f, 1.0f }, "An Error occured, during texture-loading!");
			if (ImGuiTulip::ButtonPrimarySmall("OK")) ImGui::CloseCurrentPopup();
			if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Enter)) ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		ImGui::End();
		ImGui::ShowDemoWindow();
	}


}