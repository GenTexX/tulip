#pragma once
#include "../global/global.h"

#include <tulip.h>

#include <imgui.h>

namespace tulip {

	class BaseLayer : public Layer {
	public:
		BaseLayer(Ref<GlobalManager> global);
		~BaseLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(const float& delta) override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;
	private:
		Ref<GlobalManager> m_global;

	};

}