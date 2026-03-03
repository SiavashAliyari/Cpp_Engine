#pragma once

#include "Render/VertexArray.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Texture/Texture.h"
#include "glm/glm.hpp"

namespace Core {
	struct PostProcessingSpecification {
		bool ghosted;
		bool tint;
		bool vignette;
		glm::vec4 tintColor;
		float vignetteStrength=0.4f;
		float vignetteRadius=0.75f;
		float vignetteSoftness= 0.35f;
	};
	class FullScreenRect {
	public:
		FullScreenRect();
		void Init();
		void Draw(unsigned int textureID);
		PostProcessingSpecification& GetSpec() { return m_Spec; }
	private:
		Core::Shader m_Shader;
		std::unique_ptr<Core::VertexArray> m_Vao;
		std::unique_ptr<Core::VertexBuffer> m_Vbo;
		std::unique_ptr<Core::IndexBuffer> m_Ibo;
		unsigned int m_Texture=0;
		PostProcessingSpecification m_Spec{false,false};

	};
}