#pragma once

#include "../panel.h"

#include <string>
#include "../../util/contentbrowser/contentBrowser.h"

namespace tulip {

	class BrowserPanel : public Panel {
	public:
		BrowserPanel();
		~BrowserPanel();

		virtual void onImGuiRender();
	private:
		ContentBrowser m_browser;

	};


}