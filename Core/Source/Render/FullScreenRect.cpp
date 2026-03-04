#include "FullScreenRect.h"
#include "glad/glad.h"

namespace Core {
	FullScreenRect::FullScreenRect()
		:m_Shader("../Core/res/Shaders/PostProcessing.shader"), m_Texture(0), m_Spec{false,false,false} {}

	void FullScreenRect::Init() {
		m_Vao=std::make_unique<VertexArray>();

		float vertices[] = {
			// pos (x,y,z)          // uv
			-1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,     1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,     1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f,     0.0f, 1.0f
		};
		unsigned int indecies[] = {
			0,1,2,
			2,3,0
		};

		m_Shader.Init();

		//m_Shader.SetUniform4f("u_Color", 0.1f, 1.1f, 1.2f, 1.0f);
		//m_Shader.SetUniform1i("u_Texture", m_Texture);



		m_Vbo = std::make_unique<Core::VertexBuffer>(vertices, sizeof(float) * 5 * 4);
		Core::VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_Ibo = std::make_unique<Core::IndexBuffer>(indecies, 6);
		m_Vao->AddBuffer(*m_Vbo, layout);
	}


	void FullScreenRect::Draw(unsigned int textureID, unsigned int depthTex)
	{
		glDisable(GL_DEPTH_TEST);

		m_Shader.Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		m_Shader.SetUniform1i("u_Texture", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTex);
		m_Shader.SetUniform1i("u_Depth", 1);

		m_Shader.SetUniform1i("u_blackAndWhite", m_Spec.ghosted);
		m_Shader.SetUniform1i("u_tint", m_Spec.tint);
		m_Shader.SetUniform4f("u_tint_color", m_Spec.tintColor.r, m_Spec.tintColor.g, m_Spec.tintColor.b, m_Spec.tintColor.a);

		m_Shader.SetUniform1i("u_vignette", m_Spec.vignette);
		m_Shader.SetUniform1f("u_vignetteStrength", m_Spec.vignetteStrength);
		m_Shader.SetUniform1f("u_vignetteRadius", m_Spec.vignetteRadius);
		m_Shader.SetUniform1f("u_vignetteSoftness", m_Spec.vignetteSoftness);

		m_Shader.SetUniform1i("u_fog", m_Spec.u_fog);
		m_Shader.SetUniform4f("u_fogColor", m_Spec.fogColor.r, m_Spec.fogColor.g, m_Spec.fogColor.b, m_Spec.fogColor.a);
		m_Shader.SetUniform1f("u_fogDensity", m_Spec.fogDensity);
		m_Shader.SetUniform1f("u_Near", m_Spec.near);
		m_Shader.SetUniform1f("u_Far", m_Spec.far);

		m_Vao->Bind();
		m_Ibo->Bind();
		glDrawElements(GL_TRIANGLES, m_Ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
		glEnable(GL_DEPTH_TEST);

	}

}