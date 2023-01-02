#include "global.h"

namespace tulip {

	void GlobalManager::loadFonts() {
		ImGuiTulip::loadFont("assets/fonts/NotoSans-Regular.ttf", NOTO_SANS_REGULAR);
		ImGuiTulip::loadFont("assets/fonts/NotoSans-Bold.ttf", NOTO_SANS_BOLD);
		ImGuiTulip::loadFont("assets/fonts/NotoSans-Italic.ttf", NOTO_SANS_ITALIC);
	}

}
