#include "Texture.hpp"
#include "stb_image/stb_image.h"

Texture::Texture(TEXTURE_DESC& Descriptor)
	:m_Descriptor(Descriptor), m_Channels(0)
{
	stbi_set_flip_vertically_on_load(m_Descriptor.FlipImage);
	unsigned char* Data = stbi_load(m_Descriptor.Path.c_str(),
									&m_Descriptor.Width,
									&m_Descriptor.Height,
									&m_Channels,
									0);

	glGenTextures(1, &m_ID);
	Bind();
	
	glTexImage2D(m_Descriptor.Target,
				 0,
				 m_Descriptor.InternalFormat,
				 m_Descriptor.Width,
				 m_Descriptor.Height,
				 0,
				 m_Descriptor.Format,
				 m_Descriptor.DataType,
				 Data);

	glGenerateMipmap(m_Descriptor.Target);

	glTexParameteri(m_Descriptor.Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_Descriptor.Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_Descriptor.Target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_Descriptor.Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(m_Descriptor.Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (Data) { stbi_image_free(Data); }
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_Descriptor.Slot);
	glBindTexture(m_Descriptor.Target, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(m_Descriptor.Target, 0);
}
