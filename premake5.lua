workspace "Odin"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFWm"] = "Odin/vendor/GLFWm/include"

include "Odin/vendor/GLFWm"

project "Odin"
    location "Odin"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "odpch.h"
    pchsource "Odin/src/odpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFWm}",
    }

    links
    {
        "GLFWm",
        "opengl32.lib",
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
            "OD_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "OD_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "OD_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Odin/src"
    }

    links {
        "Odin"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "OD_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "OD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "OD_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "OD_DIST"
        optimize "On"