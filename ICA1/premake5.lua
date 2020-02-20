------------------------------------------------ Solution
workspace "Game"
    configurations  { "Debug", "Release" }
    location        "build"
    startproject    "Game"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

------------------------------------------------ Game Project
project "Game"
    location    "build"
    dependson   { "Framework" }
    kind        "WindowedApp"
    language    "C++"
    debugdir    ""
    pchheader   "GamePCH.h"
    pchsource   "Game/Source/Base/WinMain.cpp"

    includedirs {
        "Game/Source",
    }

    files {
        "Game/Source/**.cpp",
        "Game/Source/**.h",
        "Data/Shaders/**.vert",
        "Data/Shaders/**.frag",
        "premake5.lua",
        "GenerateBuildFiles.bat",
        ".gitignore",
    }

    vpaths {
        [""] = {
            "*.*",
        },
        ["Source*"] = {
            "Game/Source",
        },
    }

    links {
        "Framework",
        "opengl32",
    }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

------------------------------------------------ Framework Project
project "Framework"
    location    "build"
    kind        "StaticLib"
    language    "C++"
    pchheader   "FrameworkPCH.h"
    pchsource   "Libraries/Framework/Source/Framework.cpp"

    includedirs {
        "Libraries/Framework/Source",
		"Libraries/Framework/Libraries/Box2D/include",
		"Libraries/Framework/Libraries/Box2D/src",
    }

    files {
        "Libraries/Framework/Source/**.cpp",
        "Libraries/Framework/Source/**.h",
        "Libraries/Framework/Libraries/imgui/*.cpp",
        "Libraries/Framework/Libraries/imgui/*.h",
        "Libraries/Framework/Libraries/LodePNG/lodepng.cpp",
        "Libraries/Framework/Libraries/LodePNG/lodepng.h",
        "Libraries/Framework/Libraries/Box2D/**.cpp",
        "Libraries/Framework/Libraries/Box2D/**.h",
    }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "files:Libraries/Framework/Libraries/**"
        flags   "NoPCH"

    filter "files:Libraries/Framework/Libraries/LodePNG/**"
        disablewarnings { "4551", "4334", "4267" }
