#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture2D> pTexture, 
			   const std::string initialSubTexture,
			   const std::shared_ptr<ShaderProgram> pShaderProgram, 
			   const glm::vec2& position = glm::vec2(0.f), 
			   const glm::vec2& size = glm::vec2(1.f),
			   const float rotation = 0.f);
		~Sprite();
	public:
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
	public:
		virtual void render() const;
		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotatiom(const float rotation);
	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;

		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
	};


}