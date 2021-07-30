#pragma once

#include <glad/glad.h>

namespace RenderEngine
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
		unsigned getCount() const { return m_count; }
		void init(const void* data, const unsigned count);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id;
		unsigned m_count;
	};
}