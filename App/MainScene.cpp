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
	glm::vec3 cameraPose = m_Camera.GetTransfrom().Right() * m_MoveDirection.x;
	cameraPose += m_Camera.GetTransfrom().Forward() * m_MoveDirection.y;

	m_Camera.GetTransfrom().Move(0.1f * cameraPose);

	float sens = 0.08f;
	if (m_CtrlDown)
		m_Camera.GetTransfrom().Rotate({ -m_MouseMove.x * sens, m_MouseMove.y * sens, 0.0f });



	for (auto& gameObject : m_GameObjects) {
		gameObject.OnUpdate(ts);

	}
}

void MainScene::OnEvent(Core::Event& e)
{
	Scene::OnEvent(e);

	Core::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent& ev)
	{
		int keyCode = ev.GetKeyCode();
		switch (keyCode)
		{
		case 68:
			m_MoveDirection.x = 1.0f;
			break;
		case 87:
			m_MoveDirection.y = 1.0f;
			break;
		case 83:
			m_MoveDirection.y = -1.0f;
			break;
		case 65:
			m_MoveDirection.x = -1.0f;
			break;
		case 341:
			m_CtrlDown = true;
		}
		return false;
	});
	dispatcher.Dispatch<Core::KeyReleasedEvent>([this](Core::KeyReleasedEvent& ev)
	{
		int keyCode = ev.GetKeyCode();
		switch (keyCode)
		{
		case 68:
			m_MoveDirection.x = 0.0f;
			break;
		case 87:
			m_MoveDirection.y = 0.0f;
			break;
		case 83:
			m_MoveDirection.y = 0.0f;
			break;
		case 65:
			m_MoveDirection.x = 0.0f;
			break;
		case 341:
			m_CtrlDown = false;
		}
		return false;
	});
	dispatcher.Dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& ev)
	{
		float mouseX = ev.GetY();
		float mouseY = ev.GetX();
		glm::vec2 NewMousePose{ mouseX,mouseY };
		m_MouseMove = -NewMousePose + m_MouseMoveLast;
		m_MouseMoveLast = NewMousePose;

		return false;
	});

}

