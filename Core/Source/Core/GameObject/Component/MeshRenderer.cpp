#include "MeshRenderer.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Scene/Scene.h"

namespace Core {
	MeshRenderer::MeshRenderer(const Transform& trasnform, const char* path, const std::string shaderPath)
		:m_Model(path), m_Shader(shaderPath), m_transform(trasnform)
	{
		m_Model.LoadModel();

		m_Shader.Init();
		m_Shader.Bind();
		m_Shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
		m_Shader.UnBind();

	}

	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::OnUpdate(float ts)
	{

		
	}

	void MeshRenderer::OnRender()
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f),m_transform.position);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec2 bounds = SceneManager::Get().GetActive()->GetCamera().GetBounds();

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), bounds.x/bounds.y, 0.1f, 1000.0f);
		glm::mat4 mvp = proj * view * model;

		m_Shader.Bind();
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		m_Model.Draw(m_Shader);
		m_Shader.UnBind();

	}
}

