#include <vector>
#include <glad/glad.h>
#include "Render/VertexBufferLayout.h"

namespace Core {

	template<typename T>
	void VertexBufferLayout::Push(unsigned int count) {
		static_assert(always_false<T>, "Unsupported type");
	}
	template<>
	void VertexBufferLayout::Push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}
	template<>
	void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);

	}
	template<>
	void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const { return m_Elements; }
	unsigned int VertexBufferLayout::GetStride() const { return m_Stride; }
}