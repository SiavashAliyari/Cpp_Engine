#include "ModelLayer.h"
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/ImGuiSlider.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"


ModelLayer::ModelLayer()
	:m_Shader("../Core/res/Shaders/Unlit.shader"), m_Model("../Core/res/Models/TD/TD.obj")
{
	m_Renderer = Core::Renderer();
	m_Renderer.Init();

	m_Model.LoadModel();
	m_Shader.Init();
	m_Shader.Bind();
	m_Shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
	m_Shader.UnBind();


}
ModelLayer::~ModelLayer() {

}
void ModelLayer::OnUpdate(float ts) {

}
void ModelLayer::OnRender() {
	m_Renderer.Clear();


	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), m_aspect, 0.1f, 1000.0f);
	glm::mat4 mvp = proj * view * model;

	m_Shader.Bind();
	m_Shader.SetUniformMat4f("u_MVP", mvp);
	m_Model.Draw(m_Shader);
	m_Shader.UnBind();

}
void ModelLayer::OnImguiDraw() {
	Core::ImGuiSlider::Slider(m_Rotation);
}

void ModelLayer::OnEvent(Core::Event& e)
{
	Core::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Core::WindowResizeEvent>([this](Core::WindowResizeEvent& ev)
	{
		int m_Width = ev.GetWidth();
		int m_Height = ev.GetHeight();
		m_aspect = (float)m_Width / (float)m_Height;
		return true;
	});
}
