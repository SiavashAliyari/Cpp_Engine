#include "MainScene.h"
#include "Core/GameObject/Component/MeshRenderer.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}
void MainScene::Init() {
	Core::GameObject& dog=Instantiate("dog");
	dog.SetPosition({ 5.0f,0.0f,-10.0f });
	dog.PushComponent<Core::MeshRenderer>(dog.GetTransform(),
		"../Core/res/Models/TD/TD.obj",
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
	for (auto& gameObject : m_GameObjects) {
		gameObject.OnUpdate(ts);
	}
}

void MainScene::OnEvent(Core::Event& e)
{

}

