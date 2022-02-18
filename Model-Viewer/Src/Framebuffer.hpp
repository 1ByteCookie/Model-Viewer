#pragma once
#include <glad/glad.h>
#include <memory>
#include "Texture.hpp"

class Framebuffer
{
public:
	Framebuffer(GLuint ColorSlot, int Width, int Height);
	~Framebuffer();

	void Bind() const;
	void Unbind() const;

	inline const GLuint& GetID() const { return m_ID; }
	inline const Texture* GetColor() const { return m_Color.get(); }

private:
	GLuint						m_ID;
	std::unique_ptr<Texture>	m_Color;
	GLuint						m_DepthStencil;
};