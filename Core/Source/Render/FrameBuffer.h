#pragma once
#include "glm/glm.hpp"


namespace Core {
	class FrameBuffer{
	public:
		FrameBuffer(unsigned int width,unsigned int height, bool swapChainTarget);
		~FrameBuffer();
		glm::vec2 GetSize() const { return { m_Width, m_Height }; }
		void Invalidate(); 
		void Bind();
		void UnBind();
		void Resize(const float& width, const float& height);
		unsigned int GetColorAttachment()const { return m_ColorAttachment; };

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		//true means reander to the screen used for render-passes 
		bool m_SwapChainTarget=false;
		unsigned int m_RendererID=0;
		unsigned int m_ColorAttachment=0;
		unsigned int m_DepthAttachment = 0;
	};
}