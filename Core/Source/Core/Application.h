#pragma once
#include <string>
#include <memory>
#include "Window.h"
#include "glm/glm.hpp"
#include "Layer.h"
#include "ImGui/ImGuiLayer.h"
#include "Render/FrameBuffer.h"
#include "Event/Event.h"
#include "Render/FullScreenRect.h"

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
		void OnEvent(Core::Event& e);
		glm::vec2 GetFramebufferSize()const;
		static Application& Get();
		static float GetTime();
		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer() {
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}
		FullScreenRect& GetPostProcessing() {
			return m_Rect;
		}
		glm::vec2& GetViewPortSize() { return m_ViewportSize; }

	private:
		ApplicationSpecification m_Specification;
		bool m_Running = false;
		std::shared_ptr<Window> m_Window;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

		Core::FrameBuffer m_FrameBuffer;
		Core::FrameBuffer m_PostProcessing;
		glm::vec2 m_ViewportSize{ 1280,720 };
		FullScreenRect m_Rect;

	};
}