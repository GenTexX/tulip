#include "viewportLayer.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace tulip {

	ViewportLayer::ViewportLayer(Ref<GlobalManager> global) : m_global(global) {
		m_framebuffer_texture_show = 0;
	}

	ViewportLayer::~ViewportLayer() {

	}

	void ViewportLayer::onAttach() {

		tulip::FramebufferSpec fbo_spec = {};
		fbo_spec.width = 1600;
		fbo_spec.height = 900;
		fbo_spec.attachments = { tulip::FramebufferTextureFormat::RGBA8, tulip::FramebufferTextureFormat::RGBA8, tulip::FramebufferTextureFormat::DEPTH24STENCIL8 };

		this->m_framebuffer = tulip::Framebuffer::create(fbo_spec);

		GraphicsAPI::setClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	}

	void ViewportLayer::onDetach() {
	}

	void ViewportLayer::onUpdate(const float& delta) {
		m_framebuffer->validate();
		m_framebuffer->bind();
		GraphicsAPI::clearColorBufferBit();
		GraphicsAPI::clearDepthBufferBit();
		GraphicsAPI::clearStencilBufferBit();
		drawActiveScene();
		m_framebuffer->unbind();
	}

	void ViewportLayer::onEvent(Event& e) {
		
	}

	void ViewportLayer::onImGuiRender() {


		ImGuiWindowClass wc;
		wc.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
		ImGui::SetNextWindowClass(&wc);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_MenuBar);
		ImGui::PopStyleVar();
		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("View"))	{
			if (ImGui::Selectable("Default", m_framebuffer_texture_show == 0)) {
				m_framebuffer_texture_show = 0;
			}

			if (ImGui::Selectable("Texture-Coordinates", m_framebuffer_texture_show == 1)) {
				m_framebuffer_texture_show = 1;
			}
			ImGui::EndMenu();
		}
		
		ImGui::EndMenuBar();


		uint64_t textureID = m_framebuffer->getColorAttachmentRendererID(m_framebuffer_texture_show);
		auto contentRegion = (ImGui::GetContentRegionAvail());
		ImGui::Image((void*)textureID, contentRegion);

		if (m_contentSize.x != contentRegion.x || m_contentSize.y != contentRegion.y) {
			m_framebuffer->resize(*(glm::vec2*)(&contentRegion));
			m_contentSize = *(glm::vec2*)(&contentRegion);
			m_global->activeScene()->activeCamera().getComponent<CameraComponent>().onViewResize(*(glm::vec2*)(&contentRegion));
		}

		ImGui::End();
		//ImGui::PopStyleVar();
	}

	void ViewportLayer::drawActiveScene() {
		m_global->activeScene()->editorUpdate(m_global->selectedEntity());
	}

}