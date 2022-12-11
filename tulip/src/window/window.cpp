#include "tulippch.h"
#include "window.h"
#ifdef TULIP_PLATFORM_WINDOWS
#include <platform\windows\window\windowsWindow.h>
#endif

namespace tulip {

    Ref<Window> Window::create(const int& width, const int& height, const std::string& title, const int& posX, const int& posY) {
#ifdef TULIP_PLATFORM_WINDOWS
        return createRef<WindowsWindow>(width, height, title, posX, posY);
#endif
    }

}