#include "Framebuffer.hpp"
#include "Texture.hpp"


Framebuffer::Framebuffer(GLuint ColorSlot, int Width, int Height)
{
	TEXTURE_DESC Descriptor{};
	Descriptor.Semantic			= "COLOR_ATTACHMENT";
	Descriptor.Slot				= ColorSlot;
	Descriptor.Target			= GL_TEXTURE_2D;
	Descriptor.Format			= GL_RGB;
	Descriptor.InternalFormat	= GL_RGB;
	Descriptor.DataType			= GL_UNSIGNED_BYTE;
	Descriptor.Width			= Width;
	Descriptor.Height			= Height;
	Descriptor.FlipImage		= false;
	m_Color = std::make_unique<Texture>(Descriptor);

	glGenRenderbuffers(1, &m_DepthStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

	glGenFramebuffers(1, &m_ID);
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color->GetID(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencil);

	Unbind();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_ID);
}

void Framebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void Framebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
