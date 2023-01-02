#pragma once
#include <layer\layer.h>
#include <imgui\imguiTulip.h>

#include <cstdint>

namespace tulip {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(const float& delta) override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;

		void setMenuBar(bool menubar) { m_menuBar = menubar; }

		void imGuiBegin();
		void imGuiEnd();

	private:
		static uint32_t s_instanceCounter;
		bool m_dockSpaceOpen;
		bool m_menuBar = false;

		void beginDockSpace();
		void endDockSpace();

	};

}