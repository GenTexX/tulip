#pragma once

#include "../panel.h"

namespace tulip {

	class BrowserPanel : public Panel {
	public:
		BrowserPanel();
		~BrowserPanel();

		virtual void onImGuiRender();
	private:

	};


}