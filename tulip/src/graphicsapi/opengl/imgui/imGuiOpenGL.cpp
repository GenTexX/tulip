#include "tulippch.h"

#include <application\application.h>
#include <logging\logger.h>

#ifdef TULIP_PLATFORM_WINDOWS
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_win32.cpp>
#include "imGuiOpenGL.h"
#endif // TULIP_PLATFORM_WINDOWS

namespace tulip {

	bool ImGuiOpenGL::initImpl(TulipWindowHandle hWnd) {
	
		if (!this->m_initialized) {

			TULIP_CORE_TRACE("Initializing ImGui for OpenGL...");

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.DisplaySize = ImVec2((float)Application::getMainWindow()->getWidth(), (float)Application::getMainWindow()->getHeight());
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

#ifdef TULIP_PLATFORM_WINDOWS
			ImGui_ImplWin32_Init(*hWnd, Application::getMainWindow()->getContext().glContext);
#endif  
			ImGui_ImplOpenGL3_Init("#version 410");

			this->m_initialized = true;
			TULIP_CORE_TRACE("ImGui Initialized!");

		}
		return true;
	}

	bool ImGuiOpenGL::shutDownImpl() {
		if (this->m_initialized) {
			ImGui_ImplOpenGL3_Shutdown();
#ifdef TULIP_PLATFORM_WINDOWS
			ImGui_ImplWin32_Shutdown();
#endif  
			ImGui::DestroyContext();
		}

		return true;

	}

}