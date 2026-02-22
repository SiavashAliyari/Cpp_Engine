#pragma once
#include <string>
#include <memory>
#include "Window.h"
#include "glm/glm.hpp"

namespace Core {

	struct ApplicationSpecification {
		std::string Name = "3D Engine";
		int width = 1280, height = 720 ;
	};
	class Application {
	public:
		Application(const ApplicationSpecification& specification = ApplicationSpecification());
		~Application();
		void Run();
		void Stop();
		glm::vec2 GetFramebufferSize()const;
		static Application& Get();
		static float GetTime();
	private:
		ApplicationSpecification m_Specification;
		bool m_Running = false;
		std::shared_ptr<Window> m_Window;

	};
}