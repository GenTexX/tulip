#include "tulippch.h"
#include "imGuiLayer.h"

#include <application/application.h>
#include <logging/logger.h>

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace tulip {

	uint32_t ImGuiLayer::s_instanceCounter = 0;

	ImGuiLayer::ImGuiLayer() {

		ImGuiTulip::init(Application::getMainWindow()->getWindowHandle());
		s_instanceCounter++;

	}

	ImGuiLayer::~ImGuiLayer() {
		s_instanceCounter--;

		if (s_instanceCounter <= 0) {
			ImGuiTulip::shutdown();
		}
	}

	void ImGuiLayer::onAttach() {
		this->m_dockSpaceOpen = true;
	}

	void ImGuiLayer::onDetach() {
	}

	void ImGuiLayer::onUpdate(const float& delta) {
	}

	void ImGuiLayer::onEvent(Event& e) {
	}

	void ImGuiLayer::onImGuiRender() {

	}

	void ImGuiLayer::imGuiBegin() {


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		
		ImGui::NewFrame();


		this->beginDockSpace();
	}

	void ImGuiLayer::imGuiEnd() {

		this->endDockSpace();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Application::getMainWindow()->getWidth(), (float)Application::getMainWindow()->getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			HGLRC backupContext = wglGetCurrentContext();
			HDC backupDeviceContext = wglGetCurrentDC();
			HGLRC other = Application::getMainWindow()->getContext().glContext;
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			wglMakeCurrent(backupDeviceContext, backupContext);
		}

	}

	void ImGuiLayer::beginDockSpace() {

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		if (m_menuBar)
		{
			window_flags |= ImGuiWindowFlags_MenuBar;
		}
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		} else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("dockspace", &(this->m_dockSpaceOpen), window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("dockspace"); 
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

	}

	void ImGuiLayer::endDockSpace() {

		ImGui::End();

	}
}