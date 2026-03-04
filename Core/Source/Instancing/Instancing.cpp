#include "Instancing/Instancing.h"
#include "glad/glad.h"
#include <vector>
#include <random>    
#include <cstdint>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/constants.hpp>       

#include <glm/gtc/constants.hpp>
#include "Scene/Scene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Application.h"

namespace Core {

	Instancing::Instancing() 
		:vao(0),vbo(0),ebo(0), instanceVBO(0), m_Shader("../res/Shaders/Cards.shader"),
		m_Texture("../res/Images/Brand.png") {}

	void Instancing::Init() {
		m_Shader.Init();
		m_Texture.Init();
		static VertexInstanced quadVerts[] = {
		{-0.5f,-0.5f,0.0f,   0.0f,0.0f},
		{ 0.5f,-0.5f,0.0f,   1.0f,0.0f},
		{ 0.5f, 0.5f,0.0f,   1.0f,1.0f},
		{-0.5f, 0.5f,0.0f,   0.0f,1.0f},
		};

		static unsigned int quadIdx[] = { 0,1,2, 2,3,0 };

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIdx), quadIdx, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInstanced), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInstanced), (void*)(3 * sizeof(float)));


		//3


		
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, INSTANCE_COUNT * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

		std::size_t vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * vec4Size));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * vec4Size));

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * vec4Size));

		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);

		//4

		std::vector<glm::mat4> models;
		models.resize(INSTANCE_COUNT);

		std::mt19937 rng(1337);
		std::uniform_real_distribution<float> posDist(-200.0f, 200.0f);  
		std::uniform_real_distribution<float> rotDist(0.0f, 6.283185f);   
		std::uniform_real_distribution<float> scaleDist(0.4f, 1.2f);     

		for (int i = 0; i < INSTANCE_COUNT; i++)
		{
			glm::vec3 pos(posDist(rng), posDist(rng) * 0.2f, posDist(rng)); 
			float rot = rotDist(rng);
			float s = scaleDist(rng);

			glm::mat4 m(1.0f);
			m = glm::translate(m, pos);
			m = glm::rotate(m, rot, glm::vec3(0, 1, 0)); 
			m = glm::scale(m, glm::vec3(s, s, 1.0f));  
			models[i] = m;
		}

		// Upload to GPU
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, models.size() * sizeof(glm::mat4), models.data());

	}
	void Instancing::Draw() {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		m_Shader.Bind();
		
		
		m_Texture.Bind(4);
		m_Shader.SetUniform1i("u_Texture", 4);

		Scene* activeScene = SceneManager::Get().GetActive();
		if (!activeScene) return;
		auto& camT = activeScene->GetCamera().GetTransfrom();


		glm::mat4 view(1.0f);
		view = glm::rotate(view, glm::radians(-camT.rotation.z), glm::vec3(0, 0, 1));
		view = glm::rotate(view, glm::radians(-camT.rotation.x), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(-camT.rotation.y), glm::vec3(0, 1, 0));
		view = glm::translate(view, -camT.position);

		glm::vec2 bounds = activeScene->GetCamera().GetBounds();
		if (bounds.x <= 0.0f || bounds.y <= 0.0f) {
			return;
		}


		glm::vec2& viewPortSize = Core::Application::Get().GetViewPortSize();
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), viewPortSize.x / viewPortSize.y, 0.1f, 1000.0f);
		glm::mat4 vp = proj * view;

		m_Shader.SetUniformMat4f("u_ViewProj", vp);


		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, INSTANCE_COUNT);

	}

}