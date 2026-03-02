#pragma once
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "vector"
#include "Core/GameObject/GameObject.h"
#include "Core/GameObject/Camera/Camera.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/Event.h"

namespace Core {

	class Scene {
	public:
		Scene()=default;
		virtual ~Scene()= default;
		virtual void Init()=0;
		virtual void OnRender()=0;
		virtual void OnUpdate(const float& ts)
		{
			glm::vec3 cameraPose = m_Camera.GetTransfrom().Right() * m_MoveDirection.x;
			cameraPose += m_Camera.GetTransfrom().Forward() * m_MoveDirection.y;

			m_Camera.GetTransfrom().Move(0.1f * cameraPose);

			float sens = 0.08f;
			if (m_CtrlDown)
				m_Camera.GetTransfrom().Rotate({ -m_MouseMove.x * sens, m_MouseMove.y * sens, 0.0f });

		}
		virtual void OnEvent(Event& event)
		{
			Core::EventDispatcher dispatcher(event);

			dispatcher.Dispatch<Core::WindowResizeEvent>([this](Core::WindowResizeEvent& ev)
			{
				int width= ev.GetWidth();
				int height= ev.GetHeight();
				m_Camera.SetBounds((float)width, (float)height);
				return false;
			});
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
		Camera& GetCamera() {
			return m_Camera;
		}
		GameObject& Instantiate(const std::string& name);
		std::vector<GameObject> m_GameObjects;
	protected:
		Camera m_Camera;
		glm::vec2 m_MoveDirection{ 0.0f,0.0f };
		bool m_CtrlDown = false;
		glm::vec2 m_MouseMove{ 0.0f,0.0f };
		glm::vec2 m_MouseMoveLast{ 0.0f,0.0f };

	};

	//scene manager
	class SceneManager {
	public:
		static SceneManager& Get()
		{
			static SceneManager instance;
			return instance;
		}

		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		void SetActive(Scene* scene)
		{
			m_ActiveScene = scene;
			if (m_ActiveScene)
				m_ActiveScene->Init();
		}

		Scene* GetActive() const { return m_ActiveScene; }

	private:
		SceneManager() = default;
		Scene* m_ActiveScene = nullptr;
		


	};

}
