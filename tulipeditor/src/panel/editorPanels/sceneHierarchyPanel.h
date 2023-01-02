#pragma once
#include "../panel.h"
#include "../../global/global.h"


#include <tulip.h>


namespace tulip {

	class SceneHierarchyPanel : public Panel {
	public:
		SceneHierarchyPanel(Ref<GlobalManager> global) :m_global(global) {};
		virtual ~SceneHierarchyPanel() {}

		virtual void onImGuiRender();

	private:
		Ref<GlobalManager> m_global;

		void drawEntity(Entity entity);
	};

};