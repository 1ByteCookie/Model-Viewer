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

	glm::mat4& Transform() { return m_Transform; }
	glm::vec3& Position() { return m_Position; }
	glm::vec3& Rotation() { return m_Rotation; }

private:
	std::vector<Mesh>	m_Meshes;
	glm::mat4			m_Transform;
	glm::vec3			m_Position;
	glm::vec3			m_Rotation;

	void Load(const std::string& Path);
	void TraverseNode(const aiNode* Node, const aiScene* Scene);
	Mesh LoadMesh(const aiMesh* aiMeshObject, const aiScene* Scene);
};