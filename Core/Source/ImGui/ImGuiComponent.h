#pragma once
#include <glm/glm.hpp>


namespace Core {
	class ImGuiComponent {
	public:
		static void Slider(const char* label, glm::vec3& value, float min, float max);
		static void Slider1f(const char* label, float& value, float min, float max);
		static void Toggle(const char* label, bool& value);
		static void Text(const char* label);
		static bool ColorPicker(const char* label, glm::vec4& color);

		static void Open(const char* label);
		static void Close();

	};
}