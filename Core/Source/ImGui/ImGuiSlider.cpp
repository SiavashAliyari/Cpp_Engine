#include "ImGui/ImGuiSlider.h"
#include "imgui.h"

namespace Core {
	void ImGuiSlider::Slider(glm::vec3& value){
		ImGui::Begin("Test");
		ImGui::SliderFloat3("Translation", &value.x, 0.0f, 1280.0f);
		ImGui::End();
	}
}