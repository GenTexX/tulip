#pragma once

namespace tulip {

	class Panel {

	public:
		Panel() = default;
		virtual ~Panel() {}

		virtual void onImGuiRender() = 0;

	private:

	};

}