project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    files {
        "src/glad.c"
    }

    includedirs {
        "include"
    }