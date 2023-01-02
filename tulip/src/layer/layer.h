#pragma once
#include <event/event.h>
#include <string>

namespace tulip {

	class Layer {
	public:
		Layer(const std::string& name = "unnamed_layer") :m_name(name) {}
		virtual ~Layer() {}

		const std::string& getName() { return m_name; }

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(const float& delta) = 0;
		virtual void onEvent(Event& e) = 0;
		virtual void onImGuiRender() = 0;

	protected:
		std::string m_name;
	};

}