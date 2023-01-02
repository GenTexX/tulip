#pragma once
#include "../global/global.h"
#include "../panel/panel.h"

#include <tulip.h>

#include <imgui.h>

#include <vector>

namespace tulip {

	class MainUILayer : public Layer {
	public:
		MainUILayer(Ref<GlobalManager> global);
		~MainUILayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(const float& delta) override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;

	private:
		Ref<GlobalManager> m_global;

		std::vector<Ref<Panel>> m_panels;

	};

}