#pragma once
#include "Scene/Scene.h"
#include "glm/glm.hpp"

class MainScene :public Core::Scene {
public:
	MainScene();
	~MainScene();
	void Init() override;
	void OnRender() override;
	void OnUpdate(const float& ts) override;
	void OnEvent(Core::Event& e) override;
private:
	glm::vec2 m_MoveDirection{0.0f,0.0f};
	bool m_CtrlDown=false;
	glm::vec2 m_MouseMove{0.0f,0.0f};
	glm::vec2 m_MouseMoveLast{ 0.0f,0.0f };

};