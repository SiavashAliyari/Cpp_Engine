#include "ModelLayer.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "ImGui/ImGuiComponent.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Core/Application.h"


ModelLayer::ModelLayer()
{
	m_Renderer = Core::Renderer();
	m_Renderer.Init();

	m_scene.Init();
	Core::SceneManager::Get().SetActive(&m_scene);


}
ModelLayer::~ModelLayer() {

}
void ModelLayer::OnUpdate(float ts) {
	m_scene.OnUpdate(ts);

}
void ModelLayer::OnRender() {
	m_Renderer.Clear();
	m_scene.OnRender();
}
void ModelLayer::OnImguiDraw() {
	
	Core::ImGuiComponent::Open("Inspector");
	Core::ImGuiComponent::Slider(m_scene.GetLight().GetTransfrom().position);
	
	Core::Application& app=Core::Application::Get();
	//postprocessing options
	Core::ImGuiComponent::Toggle("Ghosted", app.GetPostProcessing().GetSpec().ghosted);
	Core::ImGuiComponent::Toggle("Tint", app.GetPostProcessing().GetSpec().tint);
	Core::ImGuiComponent::ColorPicker("Tint Color", app.GetPostProcessing().GetSpec().tintColor);

	Core::ImGuiComponent::Close();

}

void ModelLayer::OnEvent(Core::Event& e)
{
	m_scene.OnEvent(e);
}
