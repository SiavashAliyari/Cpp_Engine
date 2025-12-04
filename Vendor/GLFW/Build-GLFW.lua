project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    files {
        "src/**.c",
        "include/**.h"
    }

    includedirs {
        "include"
    }

    filter "system:windows"
        defines { "_GLFW_WIN32" }

    filter "system:linux"
        defines { "_GLFW_X11" }

    filter "system:macosx"
        defines { "_GLFW_COCOA" }
