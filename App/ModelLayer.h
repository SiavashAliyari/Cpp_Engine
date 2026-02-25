#pragma once
#include "Core/Layer.h"
#include "Core/Renderer.h"
#include "Model/Model.h"

class ModelLayer :public Core::Layer{
public:
	ModelLayer();
	virtual ~ModelLayer();

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	Core::Renderer m_Renderer;
	bool m_FirstRender = true;
	Core::Shader m_Shader;
	Core::Model m_Model;
	glm::vec3 m_Rotation{ 0.0f,90.0f,0.0f };
};