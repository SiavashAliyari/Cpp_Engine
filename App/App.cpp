#include "Core/Core.h"
#include <Core/Window.h>
#include <iostream>
#include "Core/Renderer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/VertexBufferLayout.h"
#include "Shader/Shader.h"
#include <filesystem>
#include "Texture/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Event/ApplicationEvent.h>
#include "Core/Application.h"
#include "AppLayer.h"
#include "ModelLayer.h"
#include "ImGui/ImGuiLayer.h"

//void OnEvent(Core::Event& e)
//{
//    Core::EventDispatcher dispatcher(e);
//
//    dispatcher.Dispatch<Core::WindowResizeEvent>([](Core::WindowResizeEvent& ev)
//    {
//        int m_Width = ev.GetWidth();
//        int m_Height = ev.GetHeight();
//        std::cout << m_Width << std::endl;
//        return true;
//    });
//}

int main()
{
    try
    {
        std::cout << std::filesystem::current_path() << std::endl;
        
        Core::ApplicationSpecification specification;
        specification.Name = "3D Engine";
        specification.width = 1280;
        specification.height= 720;
        Core::Application application(specification);
        //application.PushLayer<Applayer>();
        application.PushLayer<ModelLayer>();
        application.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
