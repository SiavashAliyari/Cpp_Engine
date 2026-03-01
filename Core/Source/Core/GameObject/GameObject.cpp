#include "GameObject.h"
#include <iostream>

namespace Core {

	GameObject::GameObject(std::string name)
		:m_name(name)
	{

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::OnUpdate(float ts) {
		for (auto& component : m_Components) {
			component->OnUpdate(ts);
		}
	}
	void GameObject::OnRender(){
		for (auto& component : m_Components) {
			component->OnRender();
		}

	}
}