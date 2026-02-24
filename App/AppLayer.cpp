#include "AppLayer.h"
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
#include "ImGui/ImGuiSlider.h"

Applayer::Applayer()
	: m_Shader("../Core/res/Shaders/Basic.shader")
	,m_Texture("../Core/res/Images/limoo.png")
{
	std::cout << "[Applayer] Init" << std::endl;
	
	m_Renderer = Core::Renderer();
	m_Renderer.Init();

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


	m_Shader.Bind();
	m_Shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
	m_Texture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);



	m_Vbo=std::make_unique<Core::VertexBuffer>(vertices, sizeof(float) * 5 * 4);
	Core::VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_Ibo = std::make_unique<Core::IndexBuffer>(indecies, 6);
	m_Vao.AddBuffer(*m_Vbo, layout);
}

Applayer::~Applayer()
{

}

void Applayer::OnUpdate(float ts)
{

}

void Applayer::OnRender()
{
	if (m_FirstRender) {
		m_FirstRender = false;
		std::cout << "[Applayer] OnRender" << std::endl;
	}

	m_Renderer.Clear();
	
	Core::ImGuiSlider::Slider(m_Position);


	//moving camera to the left
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	glm::mat4 mvp = proj * view * model;
	m_Shader.SetUniformMat4f("u_MVP", mvp);

	m_Renderer.Draw(m_Vao, *m_Ibo, m_Shader);
}
