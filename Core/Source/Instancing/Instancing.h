#pragma once
#include "Shader/Shader.h"
#include "Texture/Texture.h"

namespace Core {
	struct VertexInstanced {
		float px, py, pz;
		float u, v;
	};
	class Instancing {
	public:
		Instancing();
		void Draw();
		void Init();
	private:
	
		unsigned int vao=0, vbo=0, ebo=0, instanceVBO=0;
		int INSTANCE_COUNT = 100000;

		Shader m_Shader;
		Texture m_Texture;

	};
}