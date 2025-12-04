#include "Core/Core.h"
#include <Core/Window.h>
#include <iostream>

int main()
{
    try
    {
        Core::Window window(1280, 720, "GLFW Test");

        while (!window.ShouldClose())
        {
            window.PollEvents();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}