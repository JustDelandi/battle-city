#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
	public:
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
		IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
	public:
		void init(const void* data, const unsigned size);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id;
	};
}