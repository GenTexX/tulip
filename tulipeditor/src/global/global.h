#pragma once

#include <tulip.h>

#define NOTO_SANS_REGULAR "nsr"
#define NOTO_SANS_BOLD "nsb"
#define NOTO_SANS_ITALIC "nsi"

namespace tulip {
	
	class GlobalManager {

	public:
		GlobalManager() = default;
		~GlobalManager() {}

		Ref<Scene> activeScene() { return m_active_scene; }
		void activeScene(Ref<Scene> scene) { m_scene_valid = true; m_active_scene = scene; }
		bool sceneValid() { return m_scene_valid; }

		Entity selectedEntity() { return m_selected_entity; }
		void selectedEntity(Entity entity) { m_selected_entity = entity; }

		void loadFonts();

	private:
		Ref<Scene> m_active_scene;
		bool m_scene_valid;
		Entity m_selected_entity;

	};

}