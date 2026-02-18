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

int main()
{
    try
    {

        std::cout << std::filesystem::current_path() << std::endl;
        Core::Window window(1280, 720, "2d Engine");
        Core::Renderer renderer;
        renderer.Init();
        
        //3d pose and u,v
        float vertices[] = {
        -0.5f, -0.5f, 0.0f,0.0f,0.0f,
         0.5f, -0.5f, 0.0f,1.0f,0.0f,
         0.5f,  0.5f, 0.0f,1.0f,1.0f,
        -0.5f,  0.5f, 0.0f,0.0f,1.0f
        };
        unsigned int indecies[] = {
            0,1,2,
            2,3,0
        };



        Core::Shader shader("../Core/res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
        Core::Texture texture("../Core/res/Images/limoo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        Core::VertexArray vao;
        Core::VertexBuffer vbo(vertices, sizeof(float) * 5*4);
        Core::VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        vao.AddBuffer(vbo, layout);
        Core::IndexBuffer ibo(indecies, 6);
        
        while (!window.ShouldClose())
        {
            renderer.Clear();
            renderer.Draw(vao,ibo,shader);

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