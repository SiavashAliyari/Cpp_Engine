#pragma once
#include "Component.h"
#include "Model/Model.h"
#include "Shader/Shader.h"

namespace Core {
	class MeshRenderer : public Component {
	public:
		MeshRenderer(const char* path, const std::string shaderPath);
		~MeshRenderer();

		void OnUpdate(float ts) override;

		void OnRender() override;

	private:
		Core::Model m_Model;
		Core::Shader m_Shader;

	};

}