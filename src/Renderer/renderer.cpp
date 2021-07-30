#include "renderer.h"

namespace RenderEngine
{
	void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
	{
		shader.use();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::setViewPort(unsigned width, unsigned height, unsigned leftOffset, unsigned bottomOffset)
	{
		glViewport(leftOffset, bottomOffset, width, height);
	}

	std::string Renderer::getRendererString()
	{
		return (char*)glGetString(GL_RENDERER);
	}

	std::string Renderer::getVersionString()
	{
		return (char*)glGetString(GL_VERSION);
	}
}