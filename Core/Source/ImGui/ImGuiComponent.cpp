#include "ImGui/ImGuiComponent.h"
#include "imgui.h"

namespace Core {
	void ImGuiComponent::Slider(const char* label,glm::vec3& value, float min, float max){
		ImGui::SliderFloat3(label, &value.x, min, max);
	}
	void ImGuiComponent::Slider1f(const char* label,float& value,float min,float max) {
		ImGui::SliderFloat(label, &value, min, max);
	}
	void ImGuiComponent::Toggle(const char* label,bool& value) {
		ImGui::Checkbox(label, &value);
	}
	bool ImGuiComponent::ColorPicker(const char* label, glm::vec4& color) {
		return ImGui::ColorEdit4(label, &color.x,
			ImGuiColorEditFlags_DisplayRGB |
			ImGuiColorEditFlags_Float);
	}
	void ImGuiComponent::Text(const char* label) {
		ImGui::Text(label);
	}
	void ImGuiComponent::Open(const char* label) {
		ImGui::Begin(label);
	}

	void ImGuiComponent::Close() {
		ImGui::End();
	}

}