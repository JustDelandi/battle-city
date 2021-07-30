#pragma once

#include <vector>
#include <glad/glad.h>

namespace RenderEngine
{
	struct VertexBufferLayoutElement
	{
		GLuint count;
		GLenum type;
		GLboolean normalized;
		unsigned size;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();
	public:
		void reserveElements(const size_t count);
		unsigned getStride() const { return m_stride; }
		void addElementLayoutFloat(const unsigned count, const bool normalized);
		const std::vector< VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; }
	private:
		std::vector< VertexBufferLayoutElement> m_layoutElements;
		unsigned m_stride;
	};
}