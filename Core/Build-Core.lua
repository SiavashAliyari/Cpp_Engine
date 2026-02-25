project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files { "Source/**.h", "Source/**.cpp" }

    includedirs
    {
        "Source",
        "../Vendor/GLFW/include",
        "../Vendor/GLAD/include",
        "../Vendor/stb_image",
        "../Vendor/glm",
        "../Vendor/imgui",
        "../Vendor/imgui/backends",
        "%{IncludeDir.assimp_build}",
        "%{IncludeDir.assimp}"
    }

    libdirs
    {
        "%{LibDir.assimp}",
        "%{LibDir.assimp}",
        "%{LibDir.assimp_zlib}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "opengl32",
        "ImGui"
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "GLFW_INCLUDE_NONE" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
          links { "assimp-vc143-mtd", "zlibstaticd" }

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
        links { "assimp-vc143-mt", "zlibstatic" }

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        links { "assimp-vc143-mt", "zlibstatic" }

    filter {}