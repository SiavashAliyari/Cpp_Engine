#pragma once
#include "Shader/Shader.h"
#include "Mesh.h"
#include "Texture/Texture.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace Core {

	class Model
	{
	public:
		Model(const char* path);
		void Draw(Shader& shader);
		void LoadModel();
	private:
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		std::vector<Mesh> meshes;
		std::string directory;
		std::string m_path;
	};
}