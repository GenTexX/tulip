#include "profilingPanel.h"
#include <application/application.h>

#include <imgui.h>

tulip::ProfilingPanel::ProfilingPanel() {
}

tulip::ProfilingPanel::~ProfilingPanel() {
}

void tulip::ProfilingPanel::onImGuiRender() {

	ImGui::Begin("Profiling");

	for (auto result : Application::getProfiler().get())
		ImGui::Text("%s %.4fms", result.first.c_str(), result.second);

	ImGui::End();

}
