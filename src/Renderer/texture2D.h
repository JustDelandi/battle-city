#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/vec2.hpp>
#include <map>

namespace RenderEngine
{
	class Texture2D
	{
	public:
		struct SubTexture2D
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
				:
				leftBottomUV(_leftBottomUV),
				rightTopUV(_rightTopUV)
			{}

			SubTexture2D()
				:
				leftBottomUV(0.f),
				rightTopUV(1.f)
			{}
		};
	public:
		Texture2D(
			const GLuint width, 
			const GLuint height,
			const unsigned char* data, 
			const unsigned int channels, 
			const GLenum filter, 
			const GLenum wrapMode);
		~Texture2D();
	public:
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&&) = delete;
	public:
		Texture2D(Texture2D&& texture2d);
		Texture2D& operator=(Texture2D&& texture2d);
	public:
		void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		const SubTexture2D& getSubTexture(const std::string& name) const;
		unsigned width();
		unsigned height();
		void bind() const;
	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned m_width;
		unsigned m_height;
		std::map<std::string, SubTexture2D> m_subTextures;
	};
}