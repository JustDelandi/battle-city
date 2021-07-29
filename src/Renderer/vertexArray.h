#pragma once

#include "vertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace Renderer
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
	public:
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&&) noexcept;
		VertexArray(VertexArray&&) noexcept;
	public:
		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id = 0;
		unsigned m_elemetsCount = 0;
	};
}