#pragma once

#include <models/Mesh.h>
#include <shader/OpenGLShader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

class Model {
public:
	Model(const char* path);
	void Draw(OpenGLShader& shader);
private:
	std::vector<Texture> m_textures_loaded;
	std::vector<Mesh> m_meshes;
	std::string m_directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma = false);
};