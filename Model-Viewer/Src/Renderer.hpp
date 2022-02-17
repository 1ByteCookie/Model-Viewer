#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
	static Renderer Instance;

	void Clear(unsigned int Mask);
	void EndFrame(GLFWwindow* Window);

	inline float GetDeltaTime() { return m_DeltaTime; }

private:
	Renderer();
	~Renderer() = default;

	float			m_DeltaTime;
	float			m_CurrentFrame;
	float			m_PreviousFrame;
};