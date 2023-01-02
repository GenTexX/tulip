#pragma once
#include "../global/global.h"

#include <tulip.h>

namespace tulip {

	class EditorApplication : public Application {
	public:
		EditorApplication();
		virtual ~EditorApplication() {}

	private:
		Ref<GlobalManager> m_global;

		virtual void genWindow() override;
		virtual void init() override;
		virtual void run() override;
	};

}