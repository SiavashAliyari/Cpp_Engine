#pragma once
#include <iostream>
#include "Render/VertexArray.h"
#include "Render/IndexBuffer.h"
#include "Shader/Shader.h"

namespace Core {
	class Renderer {
	public:
		
		void Init();
		void Clear();
		void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader)const;
	};
}