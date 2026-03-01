#include "ModelLayer.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "ImGui/ImGuiSlider.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"



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
	Core::ImGuiSlider::Slider(m_Rotation);
}

void ModelLayer::OnEvent(Core::Event& e)
{
	//Core::EventDispatcher dispatcher(e);

	//dispatcher.Dispatch<Core::WindowResizeEvent>([this](Core::WindowResizeEvent& ev)
	//{
	//	int m_Width = ev.GetWidth();
	//	int m_Height = ev.GetHeight();
	//	m_aspect = (float)m_Width / (float)m_Height;
	//	return true;
	//});
	m_scene.OnEvent(e);
}
