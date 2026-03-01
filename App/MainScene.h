#pragma once
#include "Scene/Scene.h"

class MainScene :public Core::Scene {
public:
	MainScene();
	~MainScene();
	void Init() override;
	void OnRender() override;
	void OnUpdate(const float& ts) override;
	void OnEvent(Core::Event& e) override;

};