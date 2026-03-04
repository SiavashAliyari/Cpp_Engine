#include "MainScene.h"
#include "Core/GameObject/Component/MeshRenderer.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/Event.h"
#include <iostream>


MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}
void MainScene::Init() {
	Core::GameObject& dog = Instantiate("dog");
	dog.SetPosition({ 2.0f,0.0f,-11.0f });
	dog.SetRotation({ 0.0f,0.0f, 135.0f });
	dog.PushComponent<Core::MeshRenderer>(dog.GetTransform(),
		"../res/Models/TD/TD.obj",
		"../res/Shaders/Unlit.shader"
	);

	Core::GameObject& hawk = Instantiate("hawk");
	hawk.SetRotation({ -90.0f,180.0f, 0.0f });
	hawk.SetPosition({ 0.0f,0.0f,-10.0f });
	hawk.PushComponent<Core::MeshRenderer>(hawk.GetTransform(),
		"../res/Models/Helmet/scene.gltf",
		"../res/Shaders/Unlit.shader"
	);

	Core::GameObject& man = Instantiate("man");
	man.SetPosition({ -2.0f,0.0f,-11.0f });
	man.SetRotation({ 0.0f,0.0f, 45.0f });
	man.PushComponent<Core::MeshRenderer>(man.GetTransform(),
		"../res/Models/TD/TD.obj",
		"../res/Shaders/Unlit.shader"
	);
	m_Cards.Init();
}

void MainScene::OnRender()
{
	for (auto& gameObject : m_GameObjects) {
		gameObject.OnRender();
	}
	m_Cards.Draw();

}

void MainScene::OnUpdate(const float& ts)
{
	Scene::OnUpdate(ts);

	for (auto& gameObject : m_GameObjects) {
		gameObject.OnUpdate(ts);

	}
}

void MainScene::OnEvent(Core::Event& e)
{
	Scene::OnEvent(e);

}

