workspace "Odin"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Odin/vendor/GLFW/include"
IncludeDir["Glad"] = "Odin/vendor/Glad/include"
IncludeDir["ImGui"] = "Odin/vendor/imgui"
IncludeDir["glm"] = "Odin/vendor/glm"

include "Odin/vendor/GLFW"
include "Odin/vendor/Glad"
include "Odin/vendor/imgui"

project "Odin"
    location "Odin"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "odpch.h"
    pchsource "Odin/src/odpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
            "OD_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "OD_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "OD_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Odin/vendor/spdlog/include",
        "Odin/src",
		"Odin/vendor",
        "%{IncludeDir.glm}",
    }

    links {
        "Odin"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "OD_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "OD_DIST"
        runtime "Release"
        optimize "on"
