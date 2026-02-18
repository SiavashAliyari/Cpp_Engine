#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Core{
	struct ShaderProgramSources {
		std::string VertexSource;
		std::string FragmentSource;
	};
	class Shader {
	private:
		unsigned int m_RendererID;
		std::string m_filepath;
		ShaderProgramSources m_sources;
		std::unordered_map <std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepath);
		~Shader();
		void Bind() const;
		void UnBind() const;


		ShaderProgramSources ParseShader(const std::string& filepath);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		void DeleteShader(unsigned int& shaderProgram); 

		//uniforms
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform1i(const std::string& name, int i);
		void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);

	private:
		unsigned int GetUniformLocation(const std::string& name);
		unsigned int CompileShader(unsigned int type, const std::string source);

	};

}