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
	Core::ImGuiComponent::Text("Instructions:\n[WASD] to Move [Ctrl] and Mouse to Look");
	Core::ImGuiComponent::Slider("Light Direction", m_scene.GetLight().GetTransfrom().position,-1.0f,1.0f);
	Core::ImGuiComponent::Slider1f("Intensity", m_scene.GetLight().GetIntensity(),0.0f,2.0f);

	Core::Application& app=Core::Application::Get();
	//postprocessing options
	Core::ImGuiComponent::Toggle("Ghosted", app.GetPostProcessing().GetSpec().ghosted);
	Core::ImGuiComponent::Toggle("Tint", app.GetPostProcessing().GetSpec().tint);
	Core::ImGuiComponent::ColorPicker("Tint Color", app.GetPostProcessing().GetSpec().tintColor);
	Core::ImGuiComponent::Text("Vignette");
	Core::ImGuiComponent::Toggle("Vignette", app.GetPostProcessing().GetSpec().vignette);
	Core::ImGuiComponent::Slider1f("Radius", app.GetPostProcessing().GetSpec().vignetteRadius,0.0f,1.0f);
	Core::ImGuiComponent::Slider1f("Strength", app.GetPostProcessing().GetSpec().vignetteStrength,0.0f,1.0f);
	Core::ImGuiComponent::Slider1f("Softness", app.GetPostProcessing().GetSpec().vignetteSoftness,0.0f,1.0f);
	
	Core::ImGuiComponent::Toggle("Fog", app.GetPostProcessing().GetSpec().u_fog);
	Core::ImGuiComponent::ColorPicker("Fog Color", app.GetPostProcessing().GetSpec().fogColor);
	Core::ImGuiComponent::Slider1f("Density", app.GetPostProcessing().GetSpec().fogDensity, 0.0f, 1.0f);
	Core::ImGuiComponent::Slider1f("Near", app.GetPostProcessing().GetSpec().near, 0.0f, 1.0f);
	Core::ImGuiComponent::Slider1f("Far", app.GetPostProcessing().GetSpec().far, 0.0f, 100.0f);



	Core::ImGuiComponent::Close();

}

void ModelLayer::OnEvent(Core::Event& e)
{
	m_scene.OnEvent(e);
}
