project "tulip"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	targetdir ("../bin/" .. outputDir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "tulippch.h"
	pchsource "src/tulippch.cpp"
	

includeDir = {}
libDir = {}

--SPDLOG
includeDir["SPDLOG"] = "../vendor/spdlog/include"

--GLEW
includeDir["GLEW"] = "../vendor/GLEW/include"
libDir["GLEW"] = "../vendor/GLEW/lib"

--GLM
includeDir["GLM"] = "../vendor/glm/include"

--IMGUI
includeDir["IMGUI"] = "../vendor/imgui"

--IMGUI
includeDir["ENTT"] = "../vendor/entt"

--IMGUI
includeDir["CEREAL"] = "../vendor/cereal"

--STB
includeDir["STB"] = "../vendor/stb/include"


	files
	{
		"src/**.h",
		"src/**.cpp",
	}
	
    includedirs {
        "src",
        "../tulipscript/src",
		includeDir["SPDLOG"],
		includeDir["GLEW"],
		includeDir["GLM"],
		includeDir["IMGUI"],
		includeDir["ENTT"],
	    includeDir["CEREAL"],
	    includeDir["STB"]
	}
	

--	links {	
--		"tulipimgui",
--        "tulipstb"
--	}
--*/
	defines {
		"GLEW_STATIC"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines {
			"TULIP_PLATFORM_WINDOWS",
			"NOMINMAX",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:debug"
		defines "TULIP_DEBUG"
		runtime "debug"
		symbols "on"

    filter "configurations:pre"
    	defines "TULIP_PRE_RELEASE"
	    runtime "release"
		optimize "on"

	filter "configurations:release"
			defines "TULIP_RELEASE"
			runtime "release"
			optimize "on"