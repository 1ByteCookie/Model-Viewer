#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace AppGui
{
	void Initialize(GLFWwindow* Window);
	void CleanUp();

	void NewFrame();
	void RenderUI();

	void Viewport();
}