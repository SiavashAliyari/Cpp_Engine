#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>


namespace Core {
	void Renderer::Init() {
		glEnable(GL_DEPTH_TEST);
		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::cout << "Renderer initialized.\n";
	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		va.Bind();
		ib.Bind();
		shader.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	
	

}