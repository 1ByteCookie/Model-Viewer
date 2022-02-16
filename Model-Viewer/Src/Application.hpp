#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
public:
	static Application Instance;
	static void WindowResize(GLFWwindow* Window, int Width, int Height);

	int OnStart();

private:
	Application();
	~Application();

	GLFWwindow*		m_Window;
	unsigned int	m_Width;
	unsigned int	m_Height;
};