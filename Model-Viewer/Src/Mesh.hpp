#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 Positions;
	glm::vec3 Normals;
	glm::vec2 UV;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& Vertices, std::vector<unsigned int>& Indices);
	Mesh(Mesh&& Object) noexcept;
	~Mesh();
	
	Mesh(const Mesh& Object) = delete;

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetIndexCount() const { return m_IndexCount; }

private:
	GLuint			m_VertexArray;
	GLuint			m_VertexBuffer;
	GLuint			m_IndexBuffer;

	unsigned int	m_IndexCount;
};