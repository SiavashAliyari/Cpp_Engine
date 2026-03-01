#pragma once
#include "Core/GameObject/GameObject.h"

namespace Core {

	class Camera {
	public:
		Camera();
		~Camera();
		const Transform& GetTransfrom() const { return m_Transform; };
	private:
		Transform m_Transform{ glm::vec3{0,0,0},glm::vec3{0,0,0} };
	};

}