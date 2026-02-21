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



int main()
{
    try
    {
        std::cout << std::filesystem::current_path() << std::endl;
        Core::Window window(1280, 720, "2d Engine");
        Core::Renderer renderer;
        renderer.Init();
        
        //xyz pose and u,v
        float vertices[] = {
         0.0f,    0.0f, 0.0f,0.0f,0.0f,
         100.0f,  0.0f, 0.0f,1.0f,0.0f,
         100.0f,  100.0f, 0.0f,1.0f,1.0f,
         0.0f,  100.0f, 0.0f,0.0f,1.0f
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
        
        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f,-1.0f,1.0f);
        //moving camera to the left
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
        glm::mat4 mvp = proj * view *model;
        shader.SetUniformMat4f("u_MVP", mvp);

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