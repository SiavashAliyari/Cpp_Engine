#include "ImGui/ImGuiComponent.h"
#include "imgui.h"

namespace Core {
	void ImGuiComponent::Slider(glm::vec3& value){
		ImGui::SliderFloat3("Translation", &value.x, -100.0f, 100.0f);
	}
	void ImGuiComponent::Toggle(const char* label,bool& value) {
		ImGui::Checkbox(label, &value);
	}
	bool ImGuiComponent::ColorPicker(const char* label, glm::vec4& color) {
		return ImGui::ColorEdit4(label, &color.x,
			ImGuiColorEditFlags_DisplayRGB |
			ImGuiColorEditFlags_Float);
	}

	void ImGuiComponent::Open(const char* label) {
		ImGui::Begin(label);
	}

	void ImGuiComponent::Close() {
		ImGui::End();
	}

}