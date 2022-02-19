#include "AppGui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

AppGui::AppGui(GLFWwindow* Window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(Window, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
}

AppGui::~AppGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void AppGui::SetFrameBuffer(void* Color)
{
	m_FrameBufferColor = Color;
}

void AppGui::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport();
}

void AppGui::RenderUI()
{
	Viewport();
	Properties();
	Camera();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void AppGui::Viewport()
{
	ImGui::Begin("Viewport");
	ImGui::Image(m_FrameBufferColor, ImVec2(1280, 720), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}

void AppGui::Properties()
{
	ImGui::Begin("Properties");
	ImGui::End();
}

void AppGui::Camera()
{
	ImGui::Begin("Camera");
	ImGui::End();
}
