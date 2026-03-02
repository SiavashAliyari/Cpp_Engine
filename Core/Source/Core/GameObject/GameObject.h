#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "string"
#include "vector"
#include "Core/GameObject/Component/Component.h"
#include "memory"
#include <algorithm> 
#include <cmath>     

namespace Core {
	struct Transform {
		Transform()
			:position({ 0,0,0 }), rotation({ 0,0,0 }) {}
		Transform(glm::vec3 pose, glm::vec3 rot)
			:position(pose), rotation(rot) {}
		glm::vec3 position{ 0,0,0 };
		glm::vec3 rotation{ 0,0,0 };
	public:
		void Move(const glm::vec3& direction)
		{
			position += direction;
		}
		glm::vec3 Forward() const {
			glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0));
			glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0));
			glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1));
			glm::quat q = qYaw * qPitch * qRoll;

			return glm::normalize(q * glm::vec3(0, 0, -1));
		}
		glm::vec3 Right() const {
			glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0));
			glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0));
			glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1));
			glm::quat q = qYaw * qPitch * qRoll;

			return glm::normalize(q * glm::vec3(1, 0, 0));
		}

		glm::vec3 Up() const {
			glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0));
			glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0));
			glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1));
			glm::quat q = qYaw * qPitch * qRoll;

			return glm::normalize(q * glm::vec3(0, 1, 0));
		}
		void Rotate(const glm::vec3& deltaDegrees,
			bool clampPitch = true,
			float minPitch = -89.0f,
			float maxPitch = 89.0f,
			bool zeroRollForCamera = true)
		{
			rotation += deltaDegrees;
			if (clampPitch) {
				rotation.x = std::clamp(rotation.x, minPitch, maxPitch);
			}

			rotation.y = std::fmod(rotation.y, 360.0f);
			if (rotation.y < 0.0f) rotation.y += 360.0f;

			if (zeroRollForCamera) {
				rotation.z = 0.0f;
			}
		}


	};

	class GameObject {
	public:
		GameObject(std::string name);
		~GameObject();

		const std::string& GetName() const { return m_name; }
		const Transform& GetTransform() const { return m_transform; }
		void SetPosition(glm::vec3 pose){
			m_transform.position = pose;
		}
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