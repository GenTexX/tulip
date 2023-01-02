workspace "tulip"
	architecture "x64"
	startproject "tulipeditor"
	
	configurations
	{
		"debug",
		"pre",
		"release"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"
	
group "dependencies"
	include "vendor/imgui"
	include "vendor/stb"
group ""

group "core"
include "tulip"
include "tulipeditor"
include "tulipscript"
include "tulipscriptcore"
group ""



