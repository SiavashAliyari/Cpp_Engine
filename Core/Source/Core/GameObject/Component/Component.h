#pragma once
#include "string"

namespace Core {
	class GameObject; // forward declare

	class Component {
	public:
		virtual ~Component() = default;
		virtual void OnUpdate(float ts)=0;
		virtual void OnRender()=0;
		std::string GetName(){return m_name;}

		GameObject& GetGameObject() { return *m_GameObject; }
		const GameObject& GetGameObject() const { return *m_GameObject; }

	private:
		friend class GameObject;
		GameObject* m_GameObject = nullptr;
		std::string m_name;
	};
}