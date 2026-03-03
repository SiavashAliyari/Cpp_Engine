#pragma once

#include "Render/VertexArray.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Texture/Texture.h"

namespace Core {
	class FullScreenRect {
	public:
		FullScreenRect();
		void Init();
		void Draw(unsigned int textureID);
	private:
		Core::Shader m_Shader;
		std::unique_ptr<Core::VertexArray> m_Vao;
		std::unique_ptr<Core::VertexBuffer> m_Vbo;
		std::unique_ptr<Core::IndexBuffer> m_Ibo;
		unsigned int m_Texture=0;

	};
}