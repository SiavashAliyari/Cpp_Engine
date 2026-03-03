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
	dog.SetPosition({ 5.0f,0.0f,-10.0f });
	dog.SetRotation({ 0.0f,0.0f, 180.0f });
	dog.PushComponent<Core::MeshRenderer>(dog.GetTransform(),
		"../Core/res/Models/TD/TD.obj",
		"../Core/res/Shaders/Unlit.shader"
	);

	Core::GameObject& hawk = Instantiate("hawk");
	hawk.SetRotation({ -90.0f,180.0f, 0.0f });
	hawk.SetPosition({ 0.0f,0.0f,-10.0f });
	hawk.PushComponent<Core::MeshRenderer>(hawk.GetTransform(),
		"../Core/res/Models/Helmet/scene.gltf",
		"../Core/res/Shaders/Unlit.shader"
	);

	Core::GameObject& man = Instantiate("man");
	man.SetPosition({ -5.0f,0.0f,-10.0f });
	man.PushComponent<Core::MeshRenderer>(man.GetTransform(),
		"../Core/res/Models/TD/TD.obj",
		"../Core/res/Shaders/Unlit.shader"
	);
}

void MainScene::OnRender()
{
	for (auto& gameObject : m_GameObjects) {
		gameObject.OnRender();
	}
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

