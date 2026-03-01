#pragma once
#include "glm/glm.hpp"
#include "string"
#include "vector"
#include "Core/GameObject/Component/Component.h"
#include "memory"

namespace Core {
	struct Transform {
		Transform() 
			:position({0,0,0}),rotation({0,0,0}){}
		Transform(glm::vec3 pose,glm::vec3 rot) 
			:position(pose),rotation(rot){}
		glm::vec3 position{0,0,0};
		glm::vec3 rotation{0,0,0};
	};

	class GameObject {
	public:
		GameObject(std::string name);
		~GameObject();

		const std::string& GetName() const { return m_name; }
		const Transform& GetTransform() const { return m_transform; }
		void OnUpdate(float ts);
		void OnRender();


		template<typename T, typename... Args>
			requires std::is_base_of_v<Component, T>
		T& PushComponent(Args&&... args)
		{
			auto component = std::make_unique<T>(std::forward<Args>(args)...);

			T& ref = *component;
			m_Components.emplace_back(std::move(component));
			return ref;
		}


		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) noexcept = default;
		GameObject& operator=(GameObject&&) noexcept = default;


	private:
		std::string m_name;
		Transform m_transform;
		std::vector<std::unique_ptr<Component>> m_Components;
	};
}