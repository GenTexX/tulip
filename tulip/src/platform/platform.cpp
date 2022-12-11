#include "tulippch.h"
#include "platform.h"
#ifdef TULIP_PLATFORM_WINDOWS
#include <platform\windows\platformWindows.h>
#endif


namespace tulip {

    UniqueRef<Platform> Platform::s_instance = Platform::create();

    UniqueRef<Platform> Platform::create() {
     
#ifdef TULIP_PLATFORM_WINDOWS
        return createUniqueRef<PlatformWindows>();
#endif // TULIP_PLATFORM_WINDOWS

    }

}