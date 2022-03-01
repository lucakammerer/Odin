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
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
            "OD_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "OD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "OD_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "OD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "OD_DIST"
        runtime "Release"
        optimize "On"