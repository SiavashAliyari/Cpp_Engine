#include "MeshRenderer.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Scene/Scene.h"
#include "Core/Application.h"

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
		Scene* activeScene= SceneManager::Get().GetActive();
		auto& camT = activeScene->GetCamera().GetTransfrom();
	


		glm::mat4 view(1.0f);
		view = glm::rotate(view, glm::radians(-camT.rotation.z), glm::vec3(0, 0, 1));
		view = glm::rotate(view, glm::radians(-camT.rotation.x), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(-camT.rotation.y), glm::vec3(0, 1, 0));
		view = glm::translate(view, -camT.position);


		glm::mat4 model = glm::translate(glm::mat4(1.0f),m_transform.position);
		model = glm::rotate(model, glm::radians(m_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec2 bounds = activeScene->GetCamera().GetBounds();
		if (bounds.x <= 0.0f || bounds.y <= 0.0f) {
			return;
		}


		glm::vec2& viewPortSize=Core::Application::Get().GetViewPortSize();
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), viewPortSize.x/ viewPortSize.y, 0.1f, 1000.0f);
		glm::mat4 mvp = proj * view * model;


		Light& directional=activeScene->GetLight();
		m_Shader.Bind();
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		m_Shader.SetUniform3f("u_Directional_Light", directional.GetTransfrom().position.x, directional.GetTransfrom().position.y, directional.GetTransfrom().position.z);
		m_Shader.SetUniform1f("u_Ambient", directional.GetIntensity());
		m_Model.Draw(m_Shader);
		m_Shader.UnBind();

	}
}

