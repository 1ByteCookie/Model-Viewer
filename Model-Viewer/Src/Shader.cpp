#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vPath, const std::string& fPath)
	:m_ID(0)
{
	m_ID = Generate(
		ReadFile(vPath),
		ReadFile(fPath)
	);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::Bind() const
{
	glUseProgram(m_ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::Uniform1i(const std::string& Name, int v0)
{
	Bind();
	glUniform1i(GetUniformLocation(Name), v0);
}

void Shader::Uniform3fv(const std::string& Name, const glm::vec3& Vector)
{
	Bind();
	glUniform3fv(GetUniformLocation(Name), 1, glm::value_ptr(Vector));
}

void Shader::UniformMatrix4fv(const std::string& Name, const glm::mat4& Matrix)
{
	Bind();
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Matrix));
}

void Shader::UniformMatrix4fv(const std::string& Name, const glm::mat4&& Matrix)
{
	Bind();
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Matrix));
}

std::string Shader::ReadFile(const std::string& Path)
{
	std::ifstream File(Path);
	if (File.fail())
	{
		std::cout << "Error::" + Path << std::endl;
		return "Error";
	}

	std::string ReadLine, Content;
	while (std::getline(File, ReadLine))
	{
		Content += ReadLine + "\n";
	}

	File.close();
	return Content;
}

GLuint Shader::Compile(const std::string& Content, GLuint Type)
{
	GLuint ID = glCreateShader(Type);
	const char* Source = Content.c_str();
	glShaderSource(ID, 1, &Source, NULL);
	glCompileShader(ID);

	ErrorCheck(ID, Content, Type);

	return ID;
}

GLuint Shader::Generate(const std::string& Vertex, const std::string& Fragment)
{
	GLuint ShaderProgram = glCreateProgram();
	GLuint vShader = Compile(Vertex, GL_VERTEX_SHADER);
	GLuint fShader = Compile(Fragment, GL_FRAGMENT_SHADER);

	glAttachShader(ShaderProgram, vShader);
	glAttachShader(ShaderProgram, fShader);

	glLinkProgram(ShaderProgram); glValidateProgram(ShaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return ShaderProgram;
}

void Shader::ErrorCheck(GLuint ID, const std::string& Content, GLuint Type)
{
	int Status; char MessageLog[1024];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &Status);
	if (!Status)
	{
		glGetShaderInfoLog(ID, 1024, NULL, MessageLog);
		std::cout << "Error::Compile::" << ((GL_VERTEX_SHADER == Type) ? "VERTEX" : "FRAGMENT") << "::Shader\n"
			<< std::endl << Content << std::endl << MessageLog << std::endl;
	}
}

int Shader::GetUniformLocation(const std::string& Name)
{
	if (!m_Uniforms.contains(Name))
	{
		int Location = glGetUniformLocation(m_ID, Name.c_str());
		m_Uniforms.emplace(Name, Location);
	}

	return m_Uniforms.at(Name);
}