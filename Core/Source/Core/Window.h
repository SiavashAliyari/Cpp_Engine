#pragma once

struct GLFWwindow;
namespace Core {
	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();
		void SwapBuffers();
		void PollEvents();
		bool ShouldClose() const;
		GLFWwindow* GetNativeWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
	};
}