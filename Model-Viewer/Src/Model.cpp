#include "Model.hpp"
#include <glm/gtc/matrix_transform.hpp>

Model::Model(const std::string& Path)
{
	m_Position	= glm::vec3(0.0f);
	m_Rotation	= glm::vec3(0.0f);
	m_Transform	= glm::translate(glm::mat4(1.0f), m_Position);

	Load(Path);
}

void Model::Load(const std::string& Path)
{
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_FlipUVs);

	TraverseNode(Scene->mRootNode, Scene);
}

void Model::TraverseNode(const aiNode* Node, const aiScene* Scene)
{
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* aiMESH = Scene->mMeshes[ Node->mMeshes[i] ];
		m_Meshes.push_back( LoadMesh(aiMESH, Scene) );
	}

	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		TraverseNode( Node->mChildren[i], Scene );
	}
}

Mesh Model::LoadMesh(const aiMesh* aiMeshObject, const aiScene* Scene)
{
	std::vector<Vertex>			Vertices;
	std::vector<unsigned int>	Indices;
	
	Vertex						ExtractedVertex;
	glm::vec3					ExtractedVector;
	glm::vec2					ExtractedUV;

	for (unsigned int i = 0; i < aiMeshObject->mNumVertices; i++)
	{
		ExtractedVector.x = aiMeshObject->mVertices[i].x;			// Positions
		ExtractedVector.y = aiMeshObject->mVertices[i].y;
		ExtractedVector.z = aiMeshObject->mVertices[i].z;
		ExtractedVertex.Positions = ExtractedVector;

		ExtractedVector.x = aiMeshObject->mNormals[i].x;			// Normals
		ExtractedVector.y = aiMeshObject->mNormals[i].y;
		ExtractedVector.z = aiMeshObject->mNormals[i].z;
		ExtractedVertex.Normals = ExtractedVector;

		if (aiMeshObject->mTextureCoords)
		{
			ExtractedUV.x = aiMeshObject->mTextureCoords[0][i].x;
			ExtractedUV.y = aiMeshObject->mTextureCoords[0][i].y;
			ExtractedVertex.UV = ExtractedUV;
		}
		else
		{
			ExtractedVertex.UV = glm::vec2(0.0f);
		}

		Vertices.push_back(ExtractedVertex);
	}

	for (unsigned int i = 0; i < aiMeshObject->mNumFaces; i++)
	{
		aiFace Face = aiMeshObject->mFaces[i];
		for (unsigned int j = 0; j < Face.mNumIndices; j++)
			Indices.push_back( Face.mIndices[j] );
	}

	return Mesh(Vertices, Indices);
}
