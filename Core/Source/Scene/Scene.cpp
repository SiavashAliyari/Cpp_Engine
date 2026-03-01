#include "Scene/Scene.h"


namespace Core {

	GameObject& Scene::Instantiate(const std::string& name)
	{
		m_GameObjects.emplace_back(name);
		return m_GameObjects.back();
	}
}