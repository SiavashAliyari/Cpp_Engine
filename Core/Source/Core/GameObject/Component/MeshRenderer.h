#pragma once
#include "Component.h"
#include "Model/Model.h"
#include "Shader/Shader.h"
#include "Core/GameObject/GameObject.h"

namespace Core {
	class MeshRenderer : public Component {
	public:
		MeshRenderer(const Transform& trasnform,const char* path, const std::string shaderPath);
		~MeshRenderer();

		void OnUpdate(float ts) override;

		void OnRender() override;

	private:
		Model m_Model;
		Shader m_Shader;
		Transform m_transform;

	};

}