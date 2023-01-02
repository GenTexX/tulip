#pragma once

#include "../panel.h"

namespace tulip {

	class ProfilingPanel : public Panel {
	public:
		ProfilingPanel();
		~ProfilingPanel();

		virtual void onImGuiRender();

	private:

	};

}