#pragma once
#include "../global/global.h"

#include <tulip.h>

namespace tulip {

	class ViewportLayer : public Layer {
	public:
		ViewportLayer(Ref<GlobalManager> global);
		~ViewportLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(const float& delta) override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;
	private:
		Ref<GlobalManager> m_global;
		Ref<Framebuffer> m_framebuffer;

		RendererID m_framebuffer_texture_show;

		glm::vec2 m_contentSize;
		
		void drawActiveScene();
	
	};

}