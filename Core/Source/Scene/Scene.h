#pragma once
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "vector"
#include "Core/GameObject/GameObject.h"
#include "Core/GameObject/Camera/Camera.h"

namespace Core {


	class Scene {
	public:
		Scene()=default;
		virtual ~Scene()= default;
		virtual void Init()=0;
		virtual void OnRender()=0;
		virtual void OnUpdate(const float& ts)=0;
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

		}
		Camera& GetCamera() {
			return m_Camera;
		}
		GameObject& Instantiate(const std::string& name);
		std::vector<GameObject> m_GameObjects;
	private:
		Camera m_Camera;
	};
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
