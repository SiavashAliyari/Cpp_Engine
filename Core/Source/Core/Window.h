#pragma once
#include <functional>
#include "Event/Event.h"
#include "glm/glm.hpp"

struct GLFWwindow;
namespace Core {
	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();
		void SwapBuffers();
		void PollEvents();
		bool ShouldClose() const;
		void Destroy();
		glm::vec2 GetFramebufferSize();
		GLFWwindow* GetNativeWindow() const { return m_Window; }

		using EventCallbackFn = std::function<void(Event&)>;
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
	private:
		GLFWwindow* m_Window;

		void InitCallbacks();
		struct WindowData {
			int Width = 0, Height = 0;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}