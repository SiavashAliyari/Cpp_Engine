#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>


namespace Core {
	Renderer::Renderer() : m_VAO(0), m_VBO(0), m_ShaderProgram(0) {}
	Renderer::~Renderer() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteProgram(m_ShaderProgram);
	}
	void Renderer::Init() {
		float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};
		// VBO 
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);
		//VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		//idk yet
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//shaders
		const char* vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            void main()
            {
                gl_Position = vec4(aPos, 1.0);
            }
        )";

		const char* fragmentSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0, 0.3, 0.2, 1.0);
            }
        )";
		// compile vertex shader
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, nullptr);
		glCompileShader(vertex);

		// compile fragment shader
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, nullptr);
		glCompileShader(fragment);

		// link program
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertex);
		glAttachShader(m_ShaderProgram, fragment);
		glLinkProgram(m_ShaderProgram);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		std::cout << "Renderer initialized.\n";



	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw() {
		glUseProgram(m_ShaderProgram);	
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}
}