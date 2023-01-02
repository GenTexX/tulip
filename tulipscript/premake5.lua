	
project "tulipscript"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir("../bin/" .. outputDir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

includeDir = {}
libDir = {}

--MONO
includeDir["MONO"] = "../vendor/mono/include"
libDir["MONO"] = "../vendor/mono/lib/%{cfg.buildcfg}"

	includedirs{
		includeDir["MONO"]
	}

	libdirs	{
--        libDir["MONO"]
	}

	links {
--		"%{libDir.MONO}/libmono-static-sgen.lib"
	}
	
	defines {
	}

	linkoptions { 
		"/ignore:4099"
	 }

	flags { 
		"FatalCompileWarnings",
		"FatalLinkWarnings"
	}

	filter "system:windows"
		systemversion "latest"
		defines "TULIP_PLATFORM_WINDOWS"
		
	filter "configurations:debug"
		defines "TULIP_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:pre"
    	defines "TULIP_PRE_RELEASE"
	    runtime "release"
		optimize "on"

	filter "configurations:release"
			defines "TULIP_RELEASE"
			runtime "release"
			optimize "on"
