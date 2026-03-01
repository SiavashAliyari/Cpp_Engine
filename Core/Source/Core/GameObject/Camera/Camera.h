#pragma once
#include "Core/GameObject/GameObject.h"

namespace Core {

	class Camera {
	public:
		Camera();
		~Camera();
		const Transform& GetTransfrom() const { return m_Transform; };
		void SetBounds(const float& width,const float& height) 
		{
			bounds.x = width;
			bounds.y = height;
		}
		const glm::vec2& GetBounds() const { return bounds; }
	private:
		Transform m_Transform{ glm::vec3{0,0,0},glm::vec3{0,0,0} };
		glm::vec2 bounds{ 1280.0f,720.0f };
	};

}