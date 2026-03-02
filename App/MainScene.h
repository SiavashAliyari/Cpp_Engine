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


};