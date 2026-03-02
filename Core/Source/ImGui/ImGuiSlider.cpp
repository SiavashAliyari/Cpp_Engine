#include "ImGui/ImGuiSlider.h"
#include "imgui.h"

namespace Core {
	void ImGuiSlider::Slider(glm::vec3& value){
		ImGui::Begin("Test");
		ImGui::SliderFloat3("Translation", &value.x, -100.0f, 100.0f);
		ImGui::End();
	}
}