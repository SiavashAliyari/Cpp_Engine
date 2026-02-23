#pragma once
#include "Core/Layer.h"
#include "Core/Renderer.h"
#include "Render/VertexArray.h"
#include "Render/IndexBuffer.h"
#include "Shader/Shader.h"
#include <memory>
#include "Texture/Texture.h"


class Applayer : public Core::Layer {
public:
	Applayer();
	virtual ~Applayer();

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	Core::Renderer m_Renderer;
	Core::Shader m_Shader;
	Core::VertexArray m_Vao;
	std::unique_ptr<Core::VertexBuffer> m_Vbo;
	std::unique_ptr<Core::IndexBuffer> m_Ibo;
	Core::Texture m_Texture;
	bool m_FirstRender = true;
};