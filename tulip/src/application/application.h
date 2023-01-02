#pragma once

#include <window\window.h>
#include <core\core.h>
#include <layer\layerStack.h>
#include <imgui\layer\imGuiLayer.h>
#include <profiling\profiler.h>

namespace tulip {

	class Application {
	public:
		Application();
		virtual ~Application();

		virtual void genWindow() = 0;
		virtual void init() = 0;
		virtual void run() = 0;

		virtual void onEvent(Event& e);

		void postInit();

		static Ref<Window> getMainWindow() { return s_instance->m_mainWindow; }
		static Profiler& getProfiler() { return s_instance->m_profiler; }

	protected:
		static Application* s_instance;
		Ref<Window> m_mainWindow;
		LayerStack m_layers;
		Ref<ImGuiLayer> m_imGuiLayer;
		
		void onUpdate();

	private:
		float m_lastTime;
		Profiler m_profiler;
	};

}