project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir    ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    files
    {
       "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_widgets.cpp",
        "imgui_tables.cpp",           
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",

        "backends/imgui_impl_glfw.cpp",    
        "backends/imgui_impl_opengl3.cpp",  
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_opengl3.h",
    }

    includedirs
    {
        ".",
        "backends",
        "%{wks.location}/Vendor/GLFW/include"
    }

    filter "system:windows"
        systemversion "latest"