#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
	public:
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept;
		VertexBuffer(VertexBuffer&&) noexcept;
	public:
		void init(const void* data, const unsigned size);
		void update(const void* data, const unsigned size) const;
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id;
	};
}