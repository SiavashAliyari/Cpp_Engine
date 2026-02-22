#include "Application.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <glm/glm.hpp>
namespace Core {
	//singleton
	static Application* s_Application = nullptr;

	static void GLFWErrorCallback(int error,const char* description) {
		std::cerr << "[GLFW Error]: " << description << std::endl;
	}

	Application::Application(const ApplicationSpecification& specification)
		:m_Specification(specification)
	{
		s_Application = this;
		glfwSetErrorCallback(GLFWErrorCallback);
		m_Window = std::make_shared<Window>(specification.width, specification.height, m_Specification.Name.c_str());
	}
	Application::~Application() {
		//destroy the window
		m_Window->Destroy();
		glfwTerminate();
		s_Application = nullptr;
	}

	void Application::Run() {
		m_Running = true;
		//application loop
		while (m_Running) {
			glfwPollEvents();
			if (m_Window->ShouldClose()) {
				Stop();
				break;
			}
			//main layer update goes here   
			m_Window->SwapBuffers();
		}
	}
	void Application::Stop() {
		m_Running = false;
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