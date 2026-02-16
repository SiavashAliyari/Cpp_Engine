#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <Shader/Shader.h>
#include "Render/IndexBuffer.h"
#include "Render/VertexBuffer.h"

namespace Core {
	void Renderer::Init() {
		//shaders
		Shader::ShaderProgramSources source= Shader::ParseShader("../Core/res/Shaders/Basic.shader");
		unsigned int shaderProgram =Shader::CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(shaderProgram);
		//uniforms 
		int location = glGetUniformLocation(shaderProgram, "u_Color");
		glUniform4f(location, 0.8f, 0.1f, 0.2f, 1.0f);
		std::cout << "Renderer initialized.\n";
	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw() {
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	
	

}