#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& Vertices, std::vector<unsigned int>& Indices)
	:m_IndexCount(Indices.size())
{
	glGenVertexArrays(1, &m_VertexArray); glBindVertexArray(m_VertexArray);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::Positions));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::Normals));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::UV));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

Mesh::Mesh(Mesh&& Object) noexcept
{
	m_VertexArray	= Object.m_VertexArray;
	m_VertexBuffer	= Object.m_VertexBuffer;
	m_IndexBuffer	= Object.m_IndexBuffer;
	m_IndexCount	= Object.m_IndexCount;

	Object.m_VertexArray	= 0;
	Object.m_VertexBuffer	= 0;
	Object.m_IndexBuffer	= 0;
	Object.m_IndexCount		= 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
}

void Mesh::Bind() const
{
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
}

void Mesh::Unbind() const
{
	glBindVertexArray(0);
}
