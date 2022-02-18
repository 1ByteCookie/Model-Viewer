#pragma once
#include <glad/glad.h>
#include <string>

struct TEXTURE_DESC
{
	std::string		Path;
	std::string		Semantic;
	
	GLuint			Slot;
	GLuint			Target				= GL_TEXTURE_2D;
	GLuint			Format				= GL_RGB;
	GLuint			InternalFormat		= GL_RGB;
	GLuint			DataType			= GL_UNSIGNED_BYTE;

	int				Width;
	int				Height;
	bool			FlipImage			= true;
};

class Texture
{
public:
	Texture(TEXTURE_DESC& Dscriptor);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline const GLuint& GetID() const { return m_ID; }
	inline const TEXTURE_DESC& Descriptor() const { return m_Descriptor; }

private:
	GLuint			m_ID;
	TEXTURE_DESC	m_Descriptor;
	int				m_Channels;
};