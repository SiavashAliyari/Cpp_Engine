#include "Application.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <glm/glm.hpp>
#include "ImGui/ImGuiLayer.h"
#include "imgui.h"

namespace Core {
	//singleton
	static Application* s_Application = nullptr;

	static void GLFWErrorCallback(int error,const char* description) {
		std::cerr << "[GLFW Error]: " << description << std::endl;
	}

	Application::Application(const ApplicationSpecification& specification)
		:m_Specification(specification),m_FrameBuffer(specification.width,specification.height,false)
	{
		s_Application = this;
		glfwSetErrorCallback(GLFWErrorCallback);
		m_Window = std::make_shared<Window>(specification.width, specification.height, m_Specification.Name.c_str());
		m_Window->SetEventCallback([this](Core::Event& e)
		{
			this->OnEvent(e);
		});

		m_ImGuiLayer = std::make_unique<Core::ImGuiLayer>(*m_Window);
		m_FrameBuffer.Invalidate();
	}

	Application::~Application() {
		//destroy the window
		m_Window->Destroy();
		glfwTerminate();
		s_Application = nullptr;
	}

	void Application::Run() {
		m_Running = true;
		float lastTime = GetTime();

	
		//application loop
		while (m_Running) {
			glfwPollEvents();
			if (m_Window->ShouldClose()) {
				Stop();
				break;
			}
			//main layer update goes here
			float currentTime = GetTime();
			float timeStamp = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			
			m_FrameBuffer.Bind();
			for (const auto& layer : m_LayerStack)
				layer->OnUpdate(timeStamp);
			for (const auto& layer : m_LayerStack)
				layer->OnRender();
			m_FrameBuffer.UnBind();


			m_ImGuiLayer->Begin();
			unsigned int textureID = m_FrameBuffer.GetColorAttachment();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0 , 0 });
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize=ImGui::GetContentRegionAvail();
			if (viewportPanelSize.x != m_ViewportSize.x || viewportPanelSize.y != m_ViewportSize.y) {

				m_ViewportSize.x = viewportPanelSize.x;
				m_ViewportSize.y = viewportPanelSize.y;

				m_FrameBuffer.Resize(m_ViewportSize.x,m_ViewportSize.y);
			}

			ImGui::Image((void*)(intptr_t)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y));
			ImGui::End();
			ImGui::PopStyleVar();

			for (const auto& layer : m_LayerStack)
				layer->OnImguiDraw();
			
			m_ImGuiLayer->End();
			m_Window->SwapBuffers();

		}


	}
	void Application::Stop() {
		m_Running = false;
	}

	void Application::OnEvent(Core::Event& e)
	{
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
		}
	}

	glm::vec2 Application::GetFramebufferSize() const {
		return m_Window->GetFramebufferSize();
	}
	float Application::GetTime() {
		return (float)glfwGetTime();
	}
	Application& Application::Get() {
		return *s_Application;
	}


}