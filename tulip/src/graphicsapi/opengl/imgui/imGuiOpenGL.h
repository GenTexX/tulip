#pragma once

#include <imgui/imguiTulip.h>
#include <core/core.h>

namespace tulip {

	class ImGuiOpenGL : public ImGuiTulip {
	public:
		ImGuiOpenGL() { this->m_initialized = false; }
		virtual ~ImGuiOpenGL() {}

	private:
		virtual bool initImpl(TulipWindowHandle hWnd) override;
		virtual bool shutDownImpl() override;
	};

}