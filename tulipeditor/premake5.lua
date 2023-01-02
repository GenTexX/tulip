	
project "tulipeditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir("../bin/" .. outputDir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}


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

--MONO
includeDir["MONO"] = "../vendor/mono/include"
libDir["MONO"] = "../vendor/mono/lib/%{cfg.buildcfg}"

	includedirs {
		includeDir["SPDLOG"],
		includeDir["GLEW"],
		includeDir["GLM"],
		includeDir["IMGUI"],
		includeDir["ENTT"],
	    includeDir["CEREAL"],
	    includeDir["MONO"],
		"../tulip/src",
        "../tulipscript/src"
	}

	libdirs	{
        libDir["GLEW"],
        libDir["MONO"]
	}

	links{
        "glu32.lib",
		"glew32s.lib",
		"opengl32.lib",
        "mono-2.0-sgen",
		"tulip",
        "tulipscript",
		"tulipimgui",
        "tulipstb"
	}
	
	defines {
		"GLEW_STATIC"
	}

	linkoptions { 
        "/ignore:4099",
		"/ignore:4286"
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
        
        linkoptions { '/NODEFAULTLIB:"LIBCMT"' }
        linkoptions { '/NODEFAULTLIB:"MSVCRTD"' }
        postbuildcommands {
			'{COPY} "../vendor/mono/bin/debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

    filter "configurations:pre"
    	defines "TULIP_PRE_RELEASE"
	    runtime "release"
		optimize "on"
        postbuildcommands {
			'{COPY} "../vendor/mono/bin/release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:release"
			defines "TULIP_RELEASE"
			runtime "release"
			optimize "on"
            postbuildcommands {
			    '{COPY} "../vendor/mono/bin/release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		    }