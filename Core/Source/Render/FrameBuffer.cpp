#include "FrameBuffer.h"
#include "glad/glad.h"
#include <iostream>


namespace Core
{
	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, bool swapChainTarget) 
		:m_Width(width),m_Height(height),m_SwapChainTarget(swapChainTarget){}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);

	}

	void FrameBuffer::Invalidate()
	{
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}
		if (m_ColorAttachment)
			glDeleteTextures(1, &m_ColorAttachment);
		if (m_DepthAttachment)
			glDeleteTextures(1, &m_DepthAttachment);

		glCreateFramebuffers(1, &m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Width, m_Height);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, m_Width, m_Height);

		glNamedFramebufferTexture(m_RendererID, GL_DEPTH_STENCIL_ATTACHMENT, m_DepthAttachment, 0);

		const GLenum buffers[1] = { GL_COLOR_ATTACHMENT0 };
		glNamedFramebufferDrawBuffers(m_RendererID, 1, buffers);

		if (glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Framebuffer incomplete!\n";
	
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Resize(const float& width,const float& height)
	{

		m_Width = width;
		m_Height = height;
		Invalidate();
	}

}