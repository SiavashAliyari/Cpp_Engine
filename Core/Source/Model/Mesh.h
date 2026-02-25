#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader/Shader.h"

namespace Core {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	struct MeshTexture {
		unsigned int id;
		std::string type;
	};
	class Mesh {
	public:
		
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<MeshTexture>      textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
		void Draw(Shader& shader);
	private:
		unsigned int m_VAO, m_VBO, m_EBO;
		void setupMesh();
	};
}