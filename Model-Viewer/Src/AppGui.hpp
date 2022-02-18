#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class AppGui
{
public:
	AppGui(GLFWwindow* Window);
	~AppGui();

	void SetFrameBuffer(void* Color);

	void NewFrame();
	void RenderUI();

	// ====== User Interface =====
	void Viewport();
	void Properties();
	void Camera();
	// ====== User Interface =====

private:
	void* m_FrameBufferColor = nullptr;
};