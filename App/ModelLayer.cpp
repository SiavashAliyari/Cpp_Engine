#include "ModelLayer.h"
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/ImGuiSlider.h"

ModelLayer::ModelLayer()
	:m_Shader("../Core/res/Shaders/Unlit.shader"),m_Model("../Core/res/Models/TD/TD.obj")
{
	m_Renderer = Core::Renderer();
	m_Renderer.Init();

    m_Shader.Init();
    m_Shader.Bind();
    m_Shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
    m_Model.LoadModel();

}
ModelLayer::~ModelLayer() {

}
void ModelLayer::OnUpdate(float ts) {

}
void ModelLayer::OnRender() {
    m_Renderer.Clear();

    Core::ImGuiSlider::Slider(m_Rotation);

    float aspect = 1280.0f / 720.0f;
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
    glm::mat4 mvp = proj * view * model;
    
    m_Shader.Bind();                         
    m_Shader.SetUniformMat4f("u_MVP", mvp);
    m_Model.Draw(m_Shader);

}