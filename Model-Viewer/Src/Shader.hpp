#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vPath, const std::string& fPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void Uniform1i(const std::string& Name, int v0);
	
	void Uniform3fv(const std::string& Name, const glm::vec3& Vector);

	void UniformMatrix4fv(const std::string& Name, const glm::mat4& Matrix);
	void UniformMatrix4fv(const std::string& Name, const glm::mat4&& Matrix);

private:
	GLuint									m_ID;
	std::unordered_map<std::string, int>	m_Uniforms;

	std::string ReadFile(const std::string& Path);
	GLuint Compile(const std::string& Content, GLuint Type);
	GLuint Generate(const std::string& Vertex, const std::string& Fragment);
	void ErrorCheck(GLuint ID, const std::string& Content, GLuint Type);

	int GetUniformLocation(const std::string& Name);
};