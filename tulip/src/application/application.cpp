#include "tulippch.h"
#include "application.h"

#include <core/core.h>
#include <logging/logger.h>
#include <platform\platform.h>

namespace tulip {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		this->m_lastTime = 0;
		TULIP_CORE_TRACE("Application generated!");
	}

	Application::~Application() {
	}

	void Application::onEvent(Event& e) {
		for (auto& layer : m_layers) {
			layer->onEvent(e);
		}
	}

	void Application::postInit() {
		this->m_mainWindow->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	void Application::onUpdate() {

		float now = Platform::getTime();
		{
			TULIP_PROFILE_SCOPE("Update");
			for (Ref<Layer> layer : this->m_layers) {
				layer->onUpdate(now - this->m_lastTime);
			}
		}
		this->m_lastTime = now;

		this->m_imGuiLayer->imGuiBegin();
		{
			TULIP_PROFILE_SCOPE("ImGuiRender");
			for (Ref<Layer> layer : this->m_layers) {
				layer->onImGuiRender();
			}
		}
		this->m_imGuiLayer->imGuiEnd();

		this->m_mainWindow->update();
	}

}