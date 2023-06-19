#pragma once
#include <core/core.h>
#include <render/camera.h>

namespace tulip {

	struct ScriptComponent {
		ScriptComponent() {}
		ScriptComponent(const ScriptComponent& other) = default;
		ScriptComponent(const std::string& path) :m_script_path(path){}

		void init();
		void update();

		std::string m_script_path;
	};

}