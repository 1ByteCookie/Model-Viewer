#include "AppGui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>

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

void AppGui::SetAttributes(glm::vec3* CamPosition, glm::vec3* MeshColor, glm::vec3* DirectionalLight)
{
	m_CamPosition		= CamPosition;
	m_MeshColor			= MeshColor;
	m_DirectionalLight	= DirectionalLight;
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
	ImGui::DragFloat3(" Mesh", &m_MeshColor->x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3(" Light", &m_DirectionalLight->x, 0.01f, -1.0f, 1.0f);
	ImGui::End();
}

void AppGui::Camera()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat3(" Position", &m_CamPosition->x, 0.05f, -16.0f, 16.0f);
	ImGui::End();
}
