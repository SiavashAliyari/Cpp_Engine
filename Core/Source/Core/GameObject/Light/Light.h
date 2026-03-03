#pragma once
#include "Core/GameObject/GameObject.h"
#include "glm/glm.hpp"


namespace Core
{
	class Light {
	public:
		Transform& GetTransfrom() { return m_Transform; }
		const float& GetIntensity()const { return m_Intensity; }
		void SetIntensity(float& intensity) {
			m_Intensity = intensity;
		}
		void SetRotation(glm::vec3 rotation) {
			m_Transform.rotation = rotation;
		}
	private:
		Transform m_Transform;
		float m_Intensity=0.8f;

	};

}