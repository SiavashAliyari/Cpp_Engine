#pragma once
#include <glm/glm.hpp>


namespace Core {
	class ImGuiComponent {
	public:
		static void Slider(glm::vec3& value);
		static void Toggle(const char* label, bool& value);
		static void Open(const char* label);
		static void Close();
		static bool ColorPicker(const char* label, glm::vec4& color);

	};
}