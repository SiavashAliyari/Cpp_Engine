#include "Core/Core.h"
#include <Core/Window.h>
#include <iostream>
#include "Core/Renderer.h"

int main()
{
    try
    {
        Core::Window window(1280, 720, "GLFW Test");
        Core::Renderer renderer;
        renderer.Init();


        while (!window.ShouldClose())
        {
            renderer.Clear();
            renderer.Draw();

            window.PollEvents();
            window.SwapBuffers();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}