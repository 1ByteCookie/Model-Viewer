#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "AppGui.hpp"

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

	std::unique_ptr<AppGui> m_Gui;
};