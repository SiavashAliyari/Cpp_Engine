#pragma once
#include "Core/Layer.h"
#include "Core/Renderer.h"
#include "Model/Model.h"
#include "Event/Event.h"
#include "MainScene.h"



class ModelLayer :public Core::Layer{
public:
	ModelLayer();
	virtual ~ModelLayer();

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
	virtual void OnImguiDraw() override;
	virtual void OnEvent(Core::Event& e) override;

private:
	Core::Renderer m_Renderer;
	glm::vec3 m_Rotation{ 0.0f,0.0f,0.0f };
	float m_aspect = 1280 / 720;
	MainScene m_scene;
};