#pragma once
#include "Core/Layer.h"
#include "Core/Window.h"
namespace Core {
	class ImGuiLayer :public Layer {
	public:
		explicit ImGuiLayer(Window& window);
		~ImGuiLayer() override;

		void Begin();
		void End();
	private:
		Window* m_Window=nullptr;
	};
}