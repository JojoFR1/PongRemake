workspace "Pong"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Debug-Static",
        "Release-Static"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pong"
    location "."
    language "C++"

    targetdir ("./bin/".. outputdir)
    objdir ("./bin-int/".. outputdir)

    -- pchheader "src/pch.h"
    -- pchsource "src/pch.cpp"

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "include",
        "src"
    }
    libdirs {
        "libs/**"
    }

    buildoptions {
        "-std=gnu++17"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines "PLATFORM_WINDOWS"

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines "DEBUG"
        symbols "On"

        links {
            "sfml-graphics-d",
            "sfml-window-d",
            "sfml-system-d",
            "sfml-audio-d",
            "sfml-network-d"
        }

    filter "configurations:Release"
        kind "WindowedApp"
        defines "RELEASE"
        optimize "On"

        links {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-audio",
            "sfml-network"
        }
        
        filter "configurations:Debug-Static"
        kind "ConsoleApp"
        defines { "SFML_STATIC", "DEBUG" }
        symbols "On"

        links {
            "sfml-graphics-s-d",
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "sfml-network-s-d"
        }

    filter "configurations:Release-Static"
        kind "WindowedApp"
        defines { "SFML_STATIC", "RELEASE" }
        optimize "On"

        links {
            "sfml-graphics-s",
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
            "sfml-network-s"
        }
    
    -- Should always be linked after the SFML links
    filter "configurations:*"
        links {
            "opengl32",
            "openal32",
            "freetype",
            "winmm",
            "gdi32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",
            "ws2_32"
        }
