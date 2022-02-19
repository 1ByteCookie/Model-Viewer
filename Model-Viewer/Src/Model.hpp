#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include "Mesh.hpp"

class Model
{
public:
	Model(const std::string& Path);
	~Model() = default;

	const auto& GetMeshes() const { return m_Meshes; }

private:
	std::vector<Mesh> m_Meshes;

	void Load(const std::string& Path);
	void TraverseNode(const aiNode* Node, const aiScene* Scene);
	Mesh LoadMesh(const aiMesh* aiMeshObject, const aiScene* Scene);
};