#pragma once

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shaderProgram.h"

#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		static void setClearColor(float r, float g, float b, float a);
		static void clear();
		static void setViewPort(unsigned width, unsigned height, unsigned leftOffset, unsigned bottomOffset);

		static std::string getRendererString();
		static std::string getVersionString();
	};
}