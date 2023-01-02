#pragma once

#include "../panel.h"
#include "../../global/global.h"

#include <tulip.h>

namespace tulip {
	class EntityDetailsPanel : public Panel {
	public:
		EntityDetailsPanel(Ref<GlobalManager> global) : m_global(global) {}
		virtual ~EntityDetailsPanel() {}

		virtual void onImGuiRender() override;

	private:
		Ref<GlobalManager> m_global;
	};

}