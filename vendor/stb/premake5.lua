project "tulipstb"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files {
        "stb_image.cpp",
		"include/stb_image.h"
    }

    filter "configurations:debug"
		runtime "debug"
		symbols "on"

	filter "configurations:pre"
		runtime "release"
		optimize "on"

    filter "configurations:release"
		runtime "release"
		optimize "on"